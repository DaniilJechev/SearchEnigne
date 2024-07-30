#ifndef SEARCHENGINE_JSONGUARD_H
#define SEARCHENGINE_JSONGUARD_H

#endif //SEARCHENGINE_JSONGUARD_H

#include <filesystem>

namespace fs = std::filesystem;

void checkConfig(const fs::path& dir);
void checkRequests(const fs::path& dir);
void checkAnswers(const fs::path& dir);