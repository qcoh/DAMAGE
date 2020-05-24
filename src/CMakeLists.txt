set(SOURCES
    mmu.cpp
    mapped_memory.cpp
)

add_library(damage_lib
    STATIC
    ${SOURCES}
)

target_include_directories(damage_lib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(damage_lib
    PUBLIC
    cxx_std_20
)