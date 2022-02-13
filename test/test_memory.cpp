#include "test.h"

#include "memory.h"
#include "types.h"

SCENARIO("reading and writing words") {
  GIVEN("dummy mmu inheriting from memory") {
    struct dummy : public memory<dummy> {
      u8 data[0x100];

      u8 read_u8(u16 address) { return data[address]; }
      void write_u8(u16 address, u8 value) { data[address] = value; }
    };

    dummy d;

    rc::prop("writing to and reading from memory is invariant",
             [&d](u16 value) {
               const u16 address = *rc::gen::inRange(0, 0x100 - 1);
               d.write_u16(address, value);

               RC_ASSERT(d.read_u16(address) == value);
             });
  }
}
