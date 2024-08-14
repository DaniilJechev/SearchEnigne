cmake_minimum_required (VERSION 3.8)

set(Src
        "ConverterJSON.cpp"
        "SearchServer.cpp"
        "InvertedIndex.cpp"
        "globals.cpp"
        "JsonGuard.cpp"
        "main.cpp"
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(SearchEngine ${Src})
#qt6_add_executable(SearchEngine ${Src})

target_link_libraries(SearchEngine
        nlohmann_json::nlohmann_json
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)
target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})


find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)