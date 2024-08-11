#pragma once

#include <filesystem>

namespace fs = std::filesystem;

extern fs::path rootDir;
extern fs::path jsonDir;
extern fs::path testsDir;
extern fs::path testJsonDir;
extern fs::path mainQmlFile;

void setPaths();