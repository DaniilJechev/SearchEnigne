#include <iostream>

#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
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

}