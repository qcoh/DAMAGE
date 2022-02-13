#include "test.h"

#include "cpu.h"
#include "lr35902.h"
#include "mmu.h"

struct dummy : public memory<dummy> {
  u8 data[0x1000];

  u8 read_u8(u16 address) { return data[address]; }
  void write_u8(u16 address, u8 v) { data[address] = v; }
};

SCENARIO("ld_imm") {
  GIVEN("cpu, mmu") {
    cpu c;
    dummy d;

    rc::prop("calling ldd_imm<bc>", [&c, &d]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<bc>(c, d);

      RC_ASSERT(c.bc == c.imm);
    });
    rc::prop("calling ldd_imm<de>", [&c, &d]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<de>(c, d);

      RC_ASSERT(c.de == c.imm);
    });
    rc::prop("calling ldd_imm<hl>", [&c, &d]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<hl>(c, d);

      RC_ASSERT(c.hl == c.imm);
    });
    rc::prop("calling ldd_imm<sp>", [&c, &d]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<sp>(c, d);

      RC_ASSERT(c.sp == c.imm);
    });
  }
}
