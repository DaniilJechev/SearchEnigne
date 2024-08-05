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
        checkRequests();
        checkAnswers();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return -1;
    }

    InvertedIndex index;
    index.UpdateDocumentBase(ConverterJSON::getTextDocuments(jsonDir));
    SearchServer server(index);
    auto answers = server.search(ConverterJSON::getRequests(jsonDir));
    ConverterJSON::putAnswers(answers, jsonDir);
}