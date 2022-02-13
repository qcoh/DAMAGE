set(SOURCES
	test_word.cpp
	test_bitref.cpp
	test_memory.cpp
	test_bios.cpp
	test_mmu.cpp
	test_lr35902.cpp
)

add_executable(damage_test
	${SOURCES}
)

target_include_directories(damage_test
	PRIVATE
	include
)

target_link_libraries(damage_test
	PRIVATE
	damage_lib
	Catch2::Catch2WithMain
	rapidcheck
)

target_compile_features(damage_test
	PRIVATE
	cxx_constexpr
)

include(CTest)
include(Catch)
catch_discover_tests(damage_test)
