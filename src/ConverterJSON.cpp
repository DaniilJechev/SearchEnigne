#include "ConverterJson.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "nlohmann/json.hpp"
#include "globals.h"


std::vector<std::string> ConverterJSON::getTextDocuments() {
    std::vector<std::string> textDocuments;
    nlohmann::json configData;
    std::ifstream config(jsonDir.string() + "config.json");

    config >> configData; //ERROR
    for (const auto &it : configData["files"]) {
        fs::path path = jsonDir / it;
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "File \"" + path.filename().string() + "\" is not found" << std::endl;
            continue;
        }
        std::string fileText, line;
        while (std::getline(file, line)) {
            fileText.append(line);
        }
        file.close();
        textDocuments.push_back(fileText);
    }
    return textDocuments;
}

int ConverterJSON::getResponsesLimit() {
    nlohmann::json  configData;
    std::ifstream config (jsonDir.string() + "config.json");
    config >> configData;
    return configData["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests() {
    nlohmann::json  requestsData;
    std::ifstream requests (jsonDir.string() + "requests.json");
    requests >> requestsData;
    return requestsData["requests"];
}
