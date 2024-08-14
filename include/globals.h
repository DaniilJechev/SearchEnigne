#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace global {
    static fs::path rootDir = fs::current_path();
    static fs::path jsonDir = rootDir / "jsonFiles/";
    static fs::path resourcesDir = rootDir / "resources/";
    static fs::path mainQmlFile = rootDir / "src/qml/main.qml";
}