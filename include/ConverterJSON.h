#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct Request {
    size_t m_id;
    std::string m_request;

    Request (size_t id, std::string request);
};

class ConverterJSON {
public:
    ConverterJSON() = default;

    static std::vector<std::string> getTextDocuments(const fs::path& jsonDir);
    static int getResponsesLimit(const fs::path& jsonDir);
    static std::vector<Request> getRequests(const fs::path& jsonDir);
    static void putAnswers(std::vector<std::vector<std::pair<int, float>>>, const fs::path& jsonDir); // implement later
};