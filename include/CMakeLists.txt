set(TARGETS
        ConverterJSON
        JsonGuard
        globals
)

foreach (TARGET IN LISTS TARGETS)
    add_library(${TARGET} STATIC
            ${CMAKE_SOURCE_DIR}/src/${TARGET}.cpp)

    set_target_properties(
            ${TARGET} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )
    if(NOT(${TARGET} STREQUAL globals))
        target_link_libraries(${TARGET} PRIVATE globals)
    endif ()
endforeach ()

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(ConverterJSON PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(JsonGuard PRIVATE nlohmann_json::nlohmann_json)