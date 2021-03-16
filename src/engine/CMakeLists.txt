
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE lania_engine_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE lania_engine_headers "[a-zA-Z]*.hpp")

add_library(lania_engine SHARED
	  ${lania_engine_sources}
	  ${lania_engine_headers}
)

add_dependencies (lania_engine
	yaml_cpp
)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../../thirdparty/SDL2-2.0.14/lib/x64)

include_directories(
		../../thirdparty/SDL2-2.0.14/include
		../../thirdparty/yaml-cpp-0.6.3/include
		.
)

target_link_libraries (lania_engine
		yaml_cpp
		${SDL2}
)

add_definitions(-D_LANIA_ENGINE_EXPORTS)

add_custom_command(TARGET lania_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:lania_engine> ${PROJECT_BINARY_DIR}/main/lania_engine.dll
)