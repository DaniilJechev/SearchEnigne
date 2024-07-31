#include <filesystem>
#include <iostream>

#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "JsonGuard.h"
#include "globals.h"

int main() {
    try {
        checkConfig();
        checkAnswers();
        checkRequests();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return -1;
    }

    std::cout << "max_responses: " << ConverterJSON::getResponsesLimit() << "\n\n";

    std::cout << "Requests:" << std::endl;
    for (const auto& it : ConverterJSON::getRequests()) {
        std::cout << it << std::endl;
    }

}