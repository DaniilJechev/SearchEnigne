cmake_minimum_required(VERSION 3.5)

add_executable(main main.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        json
        URL
        https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)


target_link_libraries(main PRIVATE
        ConverterJSON
        InvertedIndex
        SearchServer
        JsonGuard
        globals
        nlohmann_json::nlohmann_json
)
