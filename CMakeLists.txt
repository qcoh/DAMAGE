cmake_minimum_required(VERSION 3.12)

project(DAMAGE)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(tests)