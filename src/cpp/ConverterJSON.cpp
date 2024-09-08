#include "ConverterJSON.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <cctype>
#include <algorithm>

#include "nlohmann/json.hpp"
#include "globals.h"
#include "AlertData.h"

namespace fs = std::filesystem;

bool Entry::operator==(const Entry &other) const {
    return (m_count == other.m_count && m_docId == other.m_docId);
}

bool RelativeIndex::operator==(const RelativeIndex &other) const {
    return (m_docId == other.m_docId && m_rank == other.m_rank);
}

ConverterJSON* ConverterJSON::converterJson = nullptr;

ConverterJSON *ConverterJSON::getInstance() {
    if (converterJson == nullptr) {
        converterJson = new ConverterJSON();
    }
    return converterJson;
}


bool ConverterJSON::isStarTerminated(const fs::path &dir) {
    std::string path = dir.string();
    return !path.empty() && path.back() == '*';
}

std::string ConverterJSON::getTextFromFile(const fs::path &filePath) {
    std::ifstream file(filePath);
    std::string fileText, line;
    while (std::getline(file, line)) {
        std::transform(line.begin(), line.end(), line.begin(),
                       [](unsigned char letter) {
                           return std::tolower(letter);
                       });
        fileText.append(line);
        if (!fileText.empty()) {
            fileText.push_back(' ');
        }
    }
    if (!fileText.empty()) fileText.pop_back(); // delete extra space
    file.close();
    return fileText;
}

bool ConverterJSON::isTxtOrDirectory(const fs::path &path) {
    return is_directory(path) || path.extension().string() == ".txt";
}

bool ConverterJSON::pathGuard(fs::path &path, const fs::path &resourcesDir) {
    if (path.empty()) {
        AlertData::appendAlert("One of your paths is empty or contain only special signs, like \"*\"",
                               AlertStates::Warning);
        return false;
    }
    if (path.is_relative()) {
        path = resourcesDir / path;
    }
    if (!ConverterJSON::isTxtOrDirectory(path)) {
        AlertData::appendAlert("Path \"" + path.string() + " does not lead to a directory or \".txt\" file",
                               AlertStates::Warning);
        return false;
    }
    if (!exists(path)) { //error
        AlertData::appendAlert( "Path \""
                               + absolute(path).string() + "\" is not exist",
                               AlertStates::Warning);
        return false;
    }
    return true;
}


std::vector<DocumentInfo> ConverterJSON::getTextDocuments(const fs::path &jsonDir,
                                                         const fs::path &resourcesDir) {
    std::vector<DocumentInfo> textDocuments;
    nlohmann::json configData;
    std::ifstream config(jsonDir / "config.json");

    config >> configData; //read all paths
    for (const auto &it: configData["paths"]) {
        fs::path path = it;
        bool checkSubdirs = ConverterJSON::isStarTerminated(path);
        if (checkSubdirs) { // delete the star
            std::string tmp = path.string();
            tmp.pop_back();
            path = tmp;
        }
        if (!ConverterJSON::pathGuard(path, resourcesDir)) continue;

        if (is_regular_file(path)) {
            textDocuments.emplace_back(ConverterJSON::getTextFromFile(path), path.string());

        } else if (is_directory(path)) {
            auto textsFromDir = ConverterJSON::getTextsFromDir(path, checkSubdirs);
            textDocuments.insert(textDocuments.end(),
                                 textsFromDir.begin(),
                                 textsFromDir.end()); // merging of new text arr with main text arr
        }
    }
    return textDocuments;
}

std::vector<DocumentInfo> ConverterJSON::getTextsFromDir(const fs::path &dir, bool checkSubdirs) {
    std::vector<DocumentInfo> textDocuments;
    for (const auto &entry: fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            textDocuments.emplace_back(ConverterJSON::getTextFromFile(entry.path()),
                                       entry.path().string());
        } else if (entry.is_directory() && checkSubdirs) {
            auto textsFromDir = ConverterJSON::getTextsFromDir(entry.path(), checkSubdirs);
            textDocuments.insert(textDocuments.end(),
                                 textsFromDir.begin(),
                                 textsFromDir.end()); // merging of new text arr with main text arr
        }
    }
    return textDocuments;
}

int ConverterJSON::getResponsesLimit(const fs::path &jsonDir) {
    nlohmann::json configData;
    std::ifstream config(jsonDir / "config.json");
    config >> configData;
    config.close();

    return configData["config"]["max_responses"];
}

void ConverterJSON::setResponsesLimit(int maxResponses, const fs::path &jsonDir) {
    nlohmann::json configData;
    std::ifstream configReading(jsonDir / "config.json");

    configReading >> configData;
    configData["config"]["max_responses"] = maxResponses;
    configReading.close();

    std::ofstream configWriting(jsonDir / "config.json");
    configWriting << configData.dump(4);
    configWriting.close();
}

std::vector<std::string> ConverterJSON::getRequests(const fs::path &jsonDir) {
    nlohmann::json data;
    std::vector<std::string> requests;
    std::ifstream file(jsonDir.string() + "requests.json");
    file >> data;

    for (const auto &it: data["requests"]) {
        std::string query = it;
        requests.push_back(query);
    }

    return requests;
}

std::vector<std::string> ConverterJSON::getPaths(const fs::path &jsonDir) {
    nlohmann::json data;
    std::vector<std::string> requests;
    std::ifstream file(jsonDir.string() + "config.json");
    file >> data;

    for (const auto &it: data["paths"]) {
        std::string path = it;
        requests.push_back(path);
    }

    return requests;
}

std::string ConverterJSON::createRequestName(int requestId) {
    std::string requestName = "request";
    if (requestId / 10 == 0) {
        requestName += "00" + std::to_string(requestId);
    } else if (requestId / 100 == 0) {
        requestName += "0" + std::to_string(requestId);
    }
    return requestName;
}

void
ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>> &relativeIndexes,
                          const fs::path &jsonDir, const std::vector<std::string>& queries) {
    nlohmann::json answerData;
    std::ofstream answers(jsonDir.string() + "answers.json");
    int requestId = 0;

    for (const auto &it: relativeIndexes) {
        std::string requestIdStr = ConverterJSON::createRequestName(requestId);
        answerData[requestIdStr]["result"] = !it.empty();
        for (const auto &it2: it) {
            answerData[requestIdStr]["relevance"]["DocId_" + std::to_string(it2.m_docId)] =
                    {{"rank",       it2.m_rank},
                     {"pathToFile", it2.m_pathToFile}};
        }
        answerData[requestIdStr]["queryText"] = queries[requestId];
        ++requestId;
    }

    if (!answerData.empty()) {
        answers << answerData.dump(4);
    } else {
        answers << "{}";
    }

    answers.close();
}

std::string ConverterJSON::getRunMode(const fs::path &jsonDir) {
    nlohmann::json configData;
    std::string path = jsonDir.string();
    std::ifstream config(jsonDir.string() + "config.json");
    config >> configData;
    if (configData["config"].contains("runMode")) {
        return configData["config"]["runMode"];
    }
    return "application";
}

void ConverterJSON::writeToJson(const QList<QString> &data, int listModelType) {
    std::string jsonFileName;
    std::string jsonArrName;
    switch (listModelType) {
        case ListModelType::Queries:
            jsonFileName = "requests.json";
            jsonArrName = "requests";
            break;

        case ListModelType::Paths:
            jsonFileName = "config.json";
            jsonArrName = "paths";
            break;

        default:
            AlertData::appendAlert("Incorrect \"writingType\"", AlertStates::Warning);
            return;
    }

    nlohmann::json myData;
    std::ifstream reading (global::jsonDir / jsonFileName);
    reading >> myData;
    reading.close();

    myData.at(jsonArrName).clear();
    for (const auto &value : data) {
        if (value.isEmpty()) continue;
        myData[jsonArrName].push_back(value.toStdString());
    }

    std::ofstream writing (global::jsonDir / jsonFileName);
    if (!myData.empty()) {
        writing << myData.dump(4);
    }
    writing.close();
}

QString ConverterJSON::getAnswers() {
    nlohmann::json data;
    std::ifstream file(global::jsonDir / "answers.json");
    file >> data;
    std::string strAnswers = data.dump(4);
    // visually separate answers
    int requestId = 1;
    std::string requestIdStr = '"' + ConverterJSON::createRequestName(requestId) + '"';
    std::string separatorAndDump = std::string(40, '-') + "\n    ";
    while (strAnswers.find(requestIdStr) != std::string::npos) {
        int pos = strAnswers.find(requestIdStr);
        strAnswers.insert(pos, separatorAndDump);
        requestId++;
        requestIdStr = '"' + ConverterJSON::createRequestName(requestId) + '"';
    }

    strAnswers = strAnswers.substr(1, strAnswers.size() - 2); // delete outmost curly brackets
    return QString::fromStdString(strAnswers);
}
