#include "test.h"

#include "bios.h"
#include "cpu.h"
#include "lr35902.h"
#include "mmu.h"
#include "registers.h"
#include "romonly.h"

SCENARIO("ld_imm") {
  GIVEN("cpu, mmu") {
    cpu c;

    u8 bios_data[0x100] = {0};
    bios b{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{b, r};

    rc::prop("calling ldd_imm<bc>", [&c, &m]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<bc>(c, m);

      RC_ASSERT(c.bc == c.imm);
    });
    rc::prop("calling ldd_imm<de>", [&c, &m]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<de>(c, m);

      RC_ASSERT(c.de == c.imm);
    });
    rc::prop("calling ldd_imm<hl>", [&c, &m]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<hl>(c, m);

      RC_ASSERT(c.hl == c.imm);
    });
    rc::prop("calling ldd_imm<sp>", [&c, &m]() {
      c.imm = *rc::gen::arbitrary<u16>();

      ld_imm<sp>(c, m);

      RC_ASSERT(c.sp == c.imm);
    });
  }
}

SCENARIO("xor") {
  GIVEN("cpu, mmu") {
    cpu cpu_;

    u8 bios_data[0x100] = {0};
    bios bios_{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{bios_, r};

    rc::prop("calling xor<b>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.b = *rc::gen::arbitrary<u8>();
      xor_<b>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.b));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<c>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.c = *rc::gen::arbitrary<u8>();
      xor_<c>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.c));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<d>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.d = *rc::gen::arbitrary<u8>();
      xor_<d>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.d));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<e>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.e = *rc::gen::arbitrary<u8>();
      xor_<e>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.e));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });

    rc::prop("calling xor<h>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.h = *rc::gen::arbitrary<u8>();
      xor_<h>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.h));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<l>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.l = *rc::gen::arbitrary<u8>();
      xor_<l>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ cpu_.l));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<at_hl>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;
      cpu_.hl = *rc::gen::inRange(0xc000, 0xcfff - 2);
      const u8 rand_at_hl = *rc::gen::arbitrary<u8>();
      m.write_u8(cpu_.hl, rand_at_hl);
      xor_<at_hl>(cpu_, m);

      RC_ASSERT(cpu_.a == (rand_a ^ rand_at_hl));
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
    rc::prop("calling xor<a>", [&cpu_, &m]() {
      const u8 rand_a = *rc::gen::arbitrary<u8>();
      cpu_.a = rand_a;

      cpu_.a = *rc::gen::arbitrary<u8>();
      xor_<a>(cpu_, m);

      RC_ASSERT(cpu_.a == 0);
      RC_ASSERT(cpu_.zf == (cpu_.a == 0));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == false);
      RC_ASSERT(cpu_.cf == false);
    });
  }
}