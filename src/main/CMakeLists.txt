
cmake_minimum_required (VERSION 3.8)

add_executable(application 
	  "application/main.cpp"
 )

 add_executable(application_high_performance_gpu 
	  "application_high_performance_gpu/main.cpp"
	  "application_high_performance_gpu/gpu.hpp"
 )

 add_executable(steam_application 
	  "steam_application/main.cpp"
 )

 add_executable(steam_application_high_performance_gpu 
	  "steam_application_high_performance_gpu/main.cpp"
	  "steam_application_high_performance_gpu/gpu.hpp"
 )

add_dependencies(application
	lania_engine
)

add_dependencies(application_high_performance_gpu
	lania_engine
)

add_dependencies(steam_application
	lania_engine
)

add_dependencies(steam_application_high_performance_gpu
	lania_engine
)

find_library(SDL2 SDL2.lib SDL2main.lib PATHS ../../thirdparty/SDL2-2.0.14/lib/x64)

include_directories(
		../../thirdparty/SDL2-2.0.14/include
		../engine
		.
)

target_link_libraries (application
		lania_engine
		${SDL2}
)

target_link_libraries (application_high_performance_gpu
		lania_engine
		${SDL2}
)

target_link_libraries (steam_application
		lania_engine
		${SDL2}
)

target_link_libraries (steam_application_high_performance_gpu
		lania_engine
		${SDL2}
)