#include "JsonGuard.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"
#include "globals.h"

void checkConfig() {
    std::ifstream config(global::jsonDir.string() + "config.json");
    if (!config.is_open()) {
        throw std::runtime_error("\"config.json\" file does not exist");
    }

    nlohmann::json data;
    try {
        config >> data;
    } catch (const std::exception &e) {
        throw std::runtime_error("\"config.json\" is empty or not in JSON format");
    }
    config.close();

    //check the "config" field
    if (!data.contains("config")) {
        throw std::runtime_error(R"(field "config" in "config.json" is not exist)");
    } else if (!data.at("config").is_object()) {
        throw std::runtime_error(R"(field "config" in "config.json" must contain key-value pairs)");
    } else if (!data["config"].contains("name")) {
        throw std::runtime_error(R"(field "name" in "config.json" is not exist)");
    } else if (!data["config"].at("name").is_string()) {
        throw std::runtime_error(R"(field "name" in "config.json" must contain a string)");
    } else if (!data["config"].contains("version")) {
        throw std::runtime_error(R"(field "version" in "config.json" is not exist)");
    } else if (!data["config"].at("version").is_string()) {
        throw std::runtime_error(R"(field "version" in "config.json" must contain a string)");
    } else if (!data["config"].contains("max_responses")) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" is not exist)");
    } else if (!data["config"].at("max_responses").is_number_integer()) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" must contain a int)");
    } else if (data["config"].at("max_responses") < 1) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" contain number less the 1)");
    }

    //check the "paths" field
    if (!data.contains("paths")) {
        throw std::runtime_error(R"(field "paths" in "config.json" is not exist)");
    } else if (!data.at("paths").is_array()) {
        throw std::runtime_error(R"(field "paths" in "config.json" must keep array elements)");
    }
    for (const auto &it: data["paths"]) {
        if (!it.is_string()) {
            throw std::runtime_error("path in \"config.json\" can't be a non-string value. "
                                     "\nError path: " + to_string(it));
        }
    }
}

void checkRequests() {
    std::ifstream requests(global::jsonDir.string() + "requests.json");
    if (!requests.is_open()) {
        throw std::runtime_error("file \"requests.json\" is not exist");
    } else if (requests.eof()) {
        throw std::runtime_error("file is empty");
    }

    nlohmann::json queries;
    try {
        requests >> queries;
    } catch (const std::exception &e) {
        throw std::runtime_error("\"requests.json\" is empty or not in JSON format");
    }
    requests.close();


    if (!queries.contains("requests")) {
        throw std::runtime_error(R"(field "requests" in "requests.json" is not exist)");
    } else if (!queries["requests"].is_array()) {
        throw std::runtime_error(R"(field "requests" in "requests.json" must keep array elements)");
    }

    int queryCnt = 0;
    for (const auto &it: queries["requests"]) {
        if (!it.is_string()) {
            throw std::runtime_error("query in \"requests.json\" can't be a non-string value. "
                                     "\nWrong query: " + to_string(it));
        }

        std::string query = it, word;
        std::stringstream stream(query);
        while (stream >> word) {
            for (char i: word) {
                if (i < 'a' or i > 'z') {
                    throw std::runtime_error("query in \"requests.json\" must contain only lowercase letters. "
                                             "\nWrong query: " + query);
                }
            }
        }
    }

    if (queryCnt > 1000) {
        throw std::runtime_error("count of queries in \"requests.json\" must be less or equal 1000");
    }
}

void checkAnswers() {
    std::ofstream answers(global::jsonDir.string() + "answers.json");
    answers.clear();
    answers.close();
}

QString GuardWrapper::checkData() {
    try {
        checkConfig();
        checkRequests();
        checkAnswers();
    } catch (const std::exception &e) {
        return e.what();
    }
    return "";
}
