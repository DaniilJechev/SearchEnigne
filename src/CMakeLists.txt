cmake_minimum_required (VERSION 3.8)

set(Src
        "cpp/main.cpp"
        "cpp/SearchServer.cpp"
        "cpp/InvertedIndex.cpp"
        "cpp/JsonGuard.cpp"
        "cpp/ConverterJSON.cpp"
        "cpp/myWindowListModel.cpp"
        "cpp/SearchHandler.cpp"
        "cpp/AlertModel.cpp"
        "cpp/DialogFinder.cpp"
        "cpp/AlertData.cpp"
        "../include/globals.h"
        "../include/SearchServer.h"
        "../include/InvertedIndex.h"
        "../include/JsonGuard.h"
        "../include/ConverterJSON.h"
        "../include/myWindowListModel.h"
        "../include/SearchHandler.h"
        "../include/AlertModel.h"
        "../include/DialogFinder.h"
        "../include/AlertData.h"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets)

add_executable(SearchEngine
    ${Src}
    qml/qml.qrc
    ../resources/icons.qrc
)

target_link_libraries(SearchEngine
        nlohmann_json::nlohmann_json
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Widgets
)

target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})
