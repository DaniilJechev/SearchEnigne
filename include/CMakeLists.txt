set(TARGETS
        ConverterJSON
        JsonGuard
)

foreach (TARGET IN LISTS TARGETS)
    add_library(${TARGET} STATIC
            ${CMAKE_SOURCE_DIR}/src/${TARGET}.cpp)

    set_target_properties(
            ${TARGET} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )
endforeach ()

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(ConverterJSON PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(JsonGuard PRIVATE ConverterJSON)