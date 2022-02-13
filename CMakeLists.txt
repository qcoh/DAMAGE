cmake_minimum_required(VERSION 3.10)

project(DAMAGE VERSION 0.1)
set(CMAKE_BUILD_TYPE "Debug")

set(SOURCES
	src/lr35902.cpp
	src/mmu.cpp
	src/gameboy.cpp
	src/bios.cpp
	src/romonly.cpp
)

add_library(damage_lib
	STATIC
	${SOURCES}
)

target_include_directories(damage_lib
	PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
)

add_executable(damage
	src/damage.cpp
)

target_link_libraries(damage
	PRIVATE
	damage_lib
)

# Tests

add_subdirectory("third-party/Catch2")
list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")

add_subdirectory("third-party/rapidcheck")

enable_testing()
add_subdirectory(test)
