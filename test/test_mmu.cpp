#include "test.h"

#include "bios.h"
#include "mapper.h"
#include "mmu.h"
#include "types.h"

#include <algorithm>
#include <iterator>

SCENARIO("toggling reading from bios and cartridge") {
  GIVEN("mmu with bios and dummy mapper") {
    struct dummy : public mapper {
      u8 data[0x200];

      u8 read_u8(u16 address) override { return data[address]; }
      void write_u8(u16 address, u8 value) override { data[address] = value; }
    };

    dummy d;
    std::fill(std::begin(d.data), std::end(d.data), 0x11);

    u8 data[0x100];
    std::fill(std::begin(data), std::end(data), 0x22);
    bios b{std::begin(data)};

    mmu m{b, d};

    WHEN("reading from an address below 0x100") {
      const u8 v = m.read_u8(0x10);
      THEN("Memory is read from the bios") { REQUIRE(v == 0x22); }
    }

    WHEN("reading from 0x100") {
      const u8 v = m.read_u8(0x100);

      THEN(
          "the reading strategy toggles and all reads are from the cartridge") {
        REQUIRE(v == 0x11);
        REQUIRE(m.read_u8(10) == 0x11);
      }
    }
  }
}
