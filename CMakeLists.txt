cmake_minimum_required(VERSION 3.10)

project(DAMAGE VERSION 0.1)

set(SOURCES
	src/foo.cpp
)

add_library(damage_lib
	STATIC
	${SOURCES}
)

target_include_directories(damage_lib
	PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
)

# Tests

add_subdirectory("third-party/Catch2")
list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")

enable_testing()
add_subdirectory(test)