set(SOURCES
    test_mmu.cpp
)

add_executable(damage_tests
    ${SOURCES}
)

target_link_libraries(damage_tests
    Catch2::Catch2WithMain
    damage_lib
)

target_compile_features(damage_tests
    PUBLIC
    cxx_std_20
)

add_test(NAME damage_tests COMMAND damage_tests)

set(SIGHANDLER_TEST_SOURCES
    test_signal_handler.cpp
)

add_executable(signal_handler_tests
    ${SIGHANDLER_TEST_SOURCES}
)

target_link_libraries(signal_handler_tests
    damage_lib
)

target_compile_features(signal_handler_tests
    PUBLIC
    cxx_std_20
)

add_test(NAME signal_handler_tests COMMAND signal_handler_tests)