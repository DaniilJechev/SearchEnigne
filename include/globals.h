#pragma once

#include <filesystem>
#include <QObject>

namespace fs = std::filesystem;

namespace global {
    static const fs::path rootDir = fs::current_path();
    static const fs::path jsonDir = rootDir / "jsonFiles/";
    static const fs::path resourcesDir = rootDir / "resources/";
    static const fs::path mainQmlFile = rootDir / "src/qml/main.qml";
}

namespace AlertStates {
    Q_NAMESPACE

    enum AlertState {
        safely = 0,
        warning = 1,
        critical = 2
    };
    Q_ENUM_NS(AlertState)
}

namespace ListModelType {
    Q_NAMESPACE

    enum ListModelType{
        queries,
        paths
    };
    Q_ENUM_NS(ListModelType);
}
