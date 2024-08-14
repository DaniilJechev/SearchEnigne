#pragma once

#include <filesystem>

namespace fs = std::filesystem;

extern fs::path rootDir;
extern fs::path jsonDir;
extern fs::path resourcesDir;
extern fs::path mainQmlFile;

void setPaths();
