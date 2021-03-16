# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("lania_engine")
project ("application")
project ("steam_application")
project ("application_high_performance_gpu")
project ("steam_application_high_performance_gpu")
project ("lania_compiled_native")

# Include sub-projects.
add_subdirectory ("engine")
add_subdirectory ("main")
add_subdirectory("editor")