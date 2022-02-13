#include "test.h"

#include "bios.h"
#include "types.h"

#include <numeric>

SCENARIO("reading from bios") {
  GIVEN("bios filled with numbers") {
    u8 data[0x100];
    std::iota(std::begin(data), std::end(data), 0);
    bios b{std::begin(data)};

    rc::prop("reading from bios at address i returns the value i", [&b]() {
      const u16 address = *rc::gen::inRange(0, 0x100);
      RC_ASSERT(b.read_u8(address) == address);
    });
  }
}
