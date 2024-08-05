#include "ConverterJson.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "nlohmann/json.hpp"
#include "SearchServer.h"

namespace fs = std::filesystem;

std::vector<std::string> ConverterJSON::getTextDocuments(const fs::path &jsonDir) {
    std::vector<std::string> textDocuments;
    nlohmann::json configData;
    std::ifstream config(jsonDir.string() + "config.json");

    config >> configData; //read all paths
    for (const auto &toFile: configData["files"]) {
        fs::path path = jsonDir / toFile;
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "File \"" + path.filename().string() + "\" is not found" << std::endl;
            continue;
        }
        std::string fileText, line;
        int lineCnt = 0;
        while (std::getline(file, line)) {
            fileText.append(line);
            ++lineCnt;
            if (lineCnt >= 1) fileText.push_back(' ');
        }
        if (!fileText.empty()) fileText.pop_back(); // delete extra space

        file.close();
        textDocuments.push_back(fileText);
    }
    return textDocuments;
}

int ConverterJSON::getResponsesLimit(const fs::path &jsonDir) {
    nlohmann::json configData;
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