
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE sources "[a-zA-Z]*.cpp")
file(GLOB_RECURSE headers "[a-zA-Z]*.hpp")

add_library(lania_compiled_native SHARED
	  ${sources}
	  ${headers}
)

add_definitions(-D_LANIA_COMPILED_NATIVE_EXPORTS)