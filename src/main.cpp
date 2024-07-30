#include <filesystem>
#include <iostream>
#include <fstream>

#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "JsonGuard.h"

namespace fs = std::filesystem;
fs::path jsonDir = "../../jsonFiles/";

int main() {
    try {
        checkConfig(jsonDir);
        checkAnswers(jsonDir);
        checkRequests(jsonDir);
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return -1;
    }

    ConverterJSON converterJson(jsonDir.string() + "requests.json" );
    converterJson.read();
    auto requests = converterJson.getData();


    //finding an answers to each query

    nlohmann::json answer
    = R"(
    {
        "answers": {
            "request001": {
                "result": "true",
                "relevance": {
                "0" : 0.989,
                "1" : 0.897,
                "2" : 0.750,
                "3" : 0.670,
                "4" : 0.561
                }
            },
            "request002": {
                "result": "true",
                "0" : 0.769
            },
            "request003": {
                "result": "false"
            }
        }
    }
    )"_json;

    converterJson.setData(answer);
    converterJson.setPath(jsonDir.string() + "answers.json");
    converterJson.write();
}