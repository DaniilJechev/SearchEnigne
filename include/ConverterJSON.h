#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "SearchServer.h"

namespace fs = std::filesystem;

class ConverterJSON {
public:
    ConverterJSON() = default;

    static std::vector<std::string> getTextDocuments(const fs::path& jsonDir);
    static int getResponsesLimit(const fs::path& jsonDir);
    static std::vector<std::string> getRequests(const fs::path& jsonDir);
    static void putAnswers(const std::vector<std::vector<RelativeIndex>> &relativeIndexes, const fs::path &jsonDir);
};