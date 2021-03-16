
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE lania_editor_sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE lania_editor_headers "[a-zA-Z]*.hpp")

add_library(lania_compiled_native SHARED
	  ${lania_editor_sources}
	  ${lania_editor_headers}
)

include_directories(
		.
)

add_definitions(-D_LANIA_COMPILED_NATIVE_EXPORTS)

add_custom_command(TARGET lania_compiled_native POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:lania_compiled_native> ${PROJECT_BINARY_DIR}/main/lania_compiled_native.dll
)