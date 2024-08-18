#include "ConverterJSON.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "nlohmann/json.hpp"
#include "SearchServer.h"

namespace fs = std::filesystem;

bool ConverterJSON::isStarTerminated(const fs::path &dir) {
    std::string path = dir.string();
    return !path.empty() && path.back() == '*';
}

std::string ConverterJSON::getTextFromFile(const fs::path& filePath) {
    std::ifstream file(filePath);
    std::string fileText, line;
    while (std::getline(file, line)) {
        fileText.append(line);
        if (!fileText.empty()) {
            fileText.push_back(' ');
        }
    }
    if (!fileText.empty()) fileText.pop_back(); // delete extra spacew
    file.close();
    return fileText;
}

bool ConverterJSON::isTxtOrDirectory(const fs::path &path) {
    return is_directory(path) || path.extension().string() == ".txt";
}

std::vector<std::string> ConverterJSON::getTextsFromDir(const fs::path &dir, bool checkSubdirs) {
    std::vector<std::string> textDocuments;
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            textDocuments.push_back(ConverterJSON::getTextFromFile(entry.path()));
        } else if (entry.is_directory() && checkSubdirs) {
            auto textsFromDir = ConverterJSON::getTextsFromDir(entry.path(), checkSubdirs);
            textDocuments.insert(textDocuments.end(),
                                 textsFromDir.begin(), textsFromDir.end()); // merging of new text arr with main text arr
        }
    }
    return textDocuments;
}

bool ConverterJSON::pathGuard(fs::path &path, const fs::path &resourcesDir) {
    if (path.empty()) {
        std::cerr << R"(One of your paths is empty or contain only special signs, like "*")"
                  << std::endl;
        return false;
    }
    if (path.is_relative()) {
        path = resourcesDir / path;
    }
    if (!ConverterJSON::isTxtOrDirectory(path)) {
        std::cerr << "Path \"" + path.string() + R"(" does not lead to a directory or ".txt" file)"
                  << std::endl;
        return false;
    }
    if (!exists(path)) { //error
        std::cerr << ((is_regular_file(path)) ? "File \"" : "Dir \"")
                  << absolute(path).string() << R"(" is not exist)"
                  << std::endl;
        return false;
    }
    return true;
}


std::vector<std::string> ConverterJSON::getTextDocuments(const fs::path &jsonDir,
                                                         const fs::path &resourcesDir) {
    std::vector<std::string> textDocuments;
    nlohmann::json configData;
    std::ifstream config(jsonDir.string() + "config.json");

    config >> configData; //read all paths
    for (const auto &it: configData["files"]) {
        fs::path path = it;
        bool checkSubdirs = ConverterJSON::isStarTerminated(path);
        if (checkSubdirs) { // delete the star
            std::string tmp = path.string();
            tmp.pop_back();
            path = tmp;
        }
        if (!ConverterJSON::pathGuard(path, resourcesDir)) continue;

        if (is_regular_file(path)) {
            textDocuments.push_back(ConverterJSON::getTextFromFile(path));

        } else if (is_directory(path)) {
            auto textsFromDir = ConverterJSON::getTextsFromDir(path, checkSubdirs);
            textDocuments.insert(textDocuments.end(),
                                 textsFromDir.begin(), textsFromDir.end()); // merging of new text arr with main text arr
        }
    }
    return textDocuments;
}

int ConverterJSON::getResponsesLimit(const fs::path &jsonDir) {
    nlohmann::json configData;
    std::string path = jsonDir.string();
    std::ifstream config(jsonDir.string() + "config.json");
    config >> configData;
    return configData["config"]["max_responses"];
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

std::string createRequestName(int requestId) {
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
                          const fs::path &jsonDir) {
    nlohmann::json answerData;
    std::ofstream answers(jsonDir.string() + "answers.json");
    int requestId = 0;

    for (const auto &it: relativeIndexes) {
        std::string requestName = createRequestName(requestId);
        answerData[requestName]["result"] = !it.empty();
        for (const auto &it2: it) {
            answerData[requestName]["relevance"].push_back({{"docId", it2.m_docId},
                                                            {"rank",  it2.m_rank}});
        }
        ++requestId;
    }
    answers << answerData.dump(4);
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