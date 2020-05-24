#include "catch2/catch_test_macros.hpp"

#include "mmu.h"

SCENARIO("Writing to and reading from MMU") {
    GIVEN("A MMU instance, an address and a value") {
        dmg::mmu mmu{};
        u16 vram_address = 0x8123;
        u8 value = 25;

        WHEN("Writing the value to address") {
            mmu[vram_address] = value;

            THEN("The value at the address is the same") {
                REQUIRE(mmu[vram_address] == value);
            }
        }
    }
}