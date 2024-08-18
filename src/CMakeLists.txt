cmake_minimum_required (VERSION 3.8)

set(Src
        "cpp/ConverterJSON.cpp"
        "cpp/SearchServer.cpp"
        "cpp/InvertedIndex.cpp"
        "cpp/JsonGuard.cpp"
        "cpp/main.cpp"
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(SearchEngine ${Src})
#qt6_add_executable(SearchEngine ${Src})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

target_link_libraries(SearchEngine
        nlohmann_json::nlohmann_json
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        )

target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})
