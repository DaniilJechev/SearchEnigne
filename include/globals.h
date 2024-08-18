#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace global {
    static const fs::path rootDir = fs::current_path();
    static const fs::path jsonDir = rootDir / "jsonFiles/";
    static const fs::path resourcesDir = rootDir / "resources/";
    static const fs::path mainQmlFile = rootDir / "src/qml/main.qml";
}