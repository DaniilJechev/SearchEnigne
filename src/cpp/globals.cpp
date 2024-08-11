#include "globals.h"
#include <filesystem>

fs::path rootDir;
fs::path jsonDir;
fs::path testDir;
fs::path testJsonDir;
fs::path mainQmlFile;

void setPaths() {
    rootDir = fs::current_path();
    while (rootDir.filename().string() != "SearchEngineProject") {
        rootDir = rootDir.parent_path();
    }
    jsonDir = rootDir / "jsonFiles/";
    testDir = rootDir / "tests/";
    testJsonDir = testDir / "testJsonFiles/";
    mainQmlFile = rootDir / "src/qml/main.qml";
}