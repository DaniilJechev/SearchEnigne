#include "globals.h"
#include <filesystem>


fs::path rootDir;
fs::path jsonDir;
fs::path resourcesDir;
fs::path mainQmlFile;

void setPaths() {
    rootDir = fs::current_path();
    while (rootDir.filename().string() != "SearchEngineProject") {
        rootDir = rootDir.parent_path();
    }
    jsonDir = rootDir / "jsonFiles/";
    resourcesDir = rootDir / "resources/";

    mainQmlFile = rootDir / "src/qml/main.qml";
}
