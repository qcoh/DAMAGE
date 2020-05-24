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

    GIVEN("A MMU instance, an address in wram0 and a value") {
        dmg::mmu mmu{};
        u16 wram_address = 0xc123;
        u8 value = 100;

        WHEN("Writing the value to the address") {
            mmu[wram_address] = value;

            THEN("The value can be read in the echo memory") {
                REQUIRE(mmu[0xe123] == value);
            }
        }
    }

    GIVEN("A MMU instance, an address in the lower echo memory and a value") {
        dmg::mmu mmu{};
        u16 wram_address = 0xe200;
        u8 value = 100;

        WHEN("Writing the value to the address") {
            mmu[wram_address] = value;

            THEN("The value can be read in wram0") {
                REQUIRE(mmu[0xc200] == value);
            }
        }
    }
}