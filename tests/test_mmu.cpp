#include "catch2/catch_test_macros.hpp"

#include "mmu.h"

SCENARIO("Writing to and reading from MMU") {
    GIVEN("A MMU instance, an address and a value") {
        dmg::mmu mmu{};
        u16 address = 123;
        u8 value = 25;

        WHEN("Writing the value to address") {
            mmu[address] = value;

            THEN("The value at the address is the same") {
                REQUIRE(mmu[address] == value);
            }
        }
    }
}