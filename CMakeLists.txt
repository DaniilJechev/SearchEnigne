cmake_minimum_required (VERSION 3.14)
project("Search-Engine")

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR
        ${CMAKE_SOURCE_DIR}/include
        )
set(MY_SRC/CPP_DIR ${CMAKE_SOURCE_DIR}/src/cpp)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)