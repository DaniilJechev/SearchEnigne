#include "JsonGuard.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

namespace fs = std::filesystem;

void checkConfig(const fs::path& dir) {
    std::ifstream file(dir.string() + "config.json");
    if (!file.is_open()) {
        throw std::runtime_error("\"config.json\" file does not exist");
    }
    file.close();
    ConverterJSON config(dir.string() + "config.json");
    try {
        config.read();
    } catch (const std::exception &e) {
        throw std::runtime_error("\"config.json\" is empty or not in JSON format");
    }

    nlohmann::json data = config.getData();

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
        throw std::runtime_error(R"(field "name" in "config.json" is not exist)");
    } else if (!data["config"].at("version").is_string()) {
        throw std::runtime_error(R"(field "version" in "config.json" must contain a string)");
    } else if (!data["config"].contains("max_responses")) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" is not exist)");
    } else if (!data["config"].at("max_responses").is_number_integer()) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" must contain a int)");
    } else if (data["config"].at("max_responses") < 1) {
        throw std::runtime_error(R"(field "max_responses" in "config.json" contain number less the 1)");
    }

    //check the "files" field
    if (!data.contains("files")) {
        throw std::runtime_error(R"(field "files" in "config.json" is not exist)");
    } else if (data["files"].empty()) {
        throw std::runtime_error(R"(field "files" in "config.json" is empty)");
    } else if (!data.at("files").is_array()) {
        throw std::runtime_error(R"(field "files" in "config.json" must keep array elements)");
    }
    for (const auto &it : data["files"]) {
        if (!it.is_string()) {
            throw std::runtime_error("path in \"config.json\" can't be a non-string value. "
                                     "\nError path: " + to_string(it));
        }
    }
}

void checkRequests(const fs::path& dir) {
    std::ifstream file(dir.string() + "requests.json");
    if (!file.is_open()) {
        throw std::runtime_error("file \"requests.json\" is not exist");
    } else if (file.eof()) {
        throw std::runtime_error("file is empty");
    }
    file.close();

    ConverterJSON request(dir.string() + "requests.json");
    try {
        request.read();
    } catch (const std::exception &e) {
        throw std::runtime_error("\"requests.json\" is empty or not in JSON format");
    }

    nlohmann::json queries = request.getData();
    if (!queries.contains("requests")) {
        throw std::runtime_error(R"(field "requests" in "requests.json" is not exist)");
    } else if (!queries["requests"].is_array()) {
        throw std::runtime_error(R"(field "requests" in "requests.json" must keep array elements)");
    }

    int queryCnt = 0;
    for (const auto & it : queries["requests"]) {
        if (!it.is_string()) {
            throw std::runtime_error("query in \"requests.json\" can't be a non-string value. "
                                     "\nWrong query: " + to_string(it));
        }

        int wordCnt = 0;
        std::string query = it, word;
        std::stringstream stream(query);
        while (stream >> word) {
            for (char i : word) {
                if (i < 'a' or i > 'z') {
                    throw std::runtime_error("query in \"requests.json\" must contain only lowercase letters. "
                                             "\nWrong query: " + query);
                }
            }
            ++wordCnt;
        }

        if (wordCnt > 10) {
            throw std::runtime_error("query in \"requests.json\" can contain maximum 10 words. "
                                     "\nWrong query: " + query);
        }
        ++queryCnt;
    }

    if (queryCnt > 1000) {
        throw std::runtime_error("count of queries in \"requests.json\" must be less or equal 1000");
    }
}

void checkAnswers(const fs::path& dir) {
    std::ofstream file(dir.string() + "answers.json");
    file << "Hello";
    file.close();
}