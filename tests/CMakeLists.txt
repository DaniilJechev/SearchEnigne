cmake_minimum_required (VERSION 3.14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${MY_SRC/CPP_DIR}/InvertedIndex.cpp
        ${MY_SRC/CPP_DIR}/SearchServer.cpp
        ${MY_SRC/CPP_DIR}/ConverterJSON.cpp
        ${MY_SRC/CPP_DIR}/AlertData.cpp

        ${MY_INCLUDE_DIR}/InvertedIndex.h
        ${MY_INCLUDE_DIR}/SearchServer.h
        ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_INCLUDE_DIR}/AlertData.h
)

set(TestsFiles
        InvertedIndexTest.cpp
        SearchServerTest.cpp
        ConverterJSONTest.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GtestTests ${TestsFiles} ${SrcFiles})
target_link_libraries(GtestTests
        nlohmann_json::nlohmann_json
        GTest::gtest_main
        Qt6::Widgets
)

include(GoogleTest)
target_include_directories(GtestTests PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(GtestTests)