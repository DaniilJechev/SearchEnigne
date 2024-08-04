cmake_minimum_required(VERSION 3.10)
project(tests)

include(FetchContent)
include(GoogleTest)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(gtest_disable_pthreads on)
enable_testing()

function(add_test TARGET)
    if (NOT TARGET) #Ensure that target name in provided
        message(FATAL_ERROR "Target name not provided to add_test function.")
    endif()

    add_executable(${TARGET} ${TARGET}.cpp)
    target_link_libraries(${TARGET} PRIVATE gtest_main globals) #necessary libraries

    foreach (LIB IN LISTS ARGN) #ARGN - list of other libraries
        target_link_libraries(${TARGET} PRIVATE ${LIB})
    endforeach ()

    gtest_discover_tests(${TARGET})
endfunction()

add_test(ConverterJSONTest ConverterJSON)
add_test(InvertedIndexTest InvertedIndex ConverterJSON)
add_test(SearchServerTest SearchServer)