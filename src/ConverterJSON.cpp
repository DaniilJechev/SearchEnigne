#include "ConverterJson.h"

#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "nlohmann/json.hpp"

namespace fs = std::filesystem;

Request::Request (size_t id, std::string request):
        m_id(id), m_request(std::move(request)) {}

std::vector<std::string> ConverterJSON::getTextDocuments(const fs::path& jsonDir) {
    std::vector<std::string> textDocuments;
    nlohmann::json configData;
    std::ifstream config(jsonDir.string() + "config.json");

    config >> configData; //read all paths
    for (const auto &toFile : configData["files"]) {
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

int ConverterJSON::getResponsesLimit(const fs::path& jsonDir) {
    nlohmann::json configData;
    std::ifstream config (jsonDir.string() + "config.json");
    config >> configData;
    return configData["config"]["max_responses"];
}

std::vector<Request> ConverterJSON::getRequests(const fs::path& jsonDir) {
    nlohmann::json data;
    std::vector<Request> requests;
    std::ifstream file (jsonDir.string() + "requests.json");
    file >> data;

    for (const auto &it : data["requests"]) {
        std::string query = it;
        if (requests.empty()) {
            requests.emplace_back(1, query);
            continue;
        }
        requests.emplace_back(requests.back().m_id + 1, query);
    }

    return requests;
}