set(SOURCES
	test_initial.cpp
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

include(CTest)
include(Catch)
catch_discover_tests(damage_test)
