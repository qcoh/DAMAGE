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

SCENARIO("inc_16") {
  GIVEN("cpu, mmu") {
    cpu c;

    u8 bios_data[0x100] = {0};
    bios b{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{b, r};

    rc::prop("calling inc_16<bc>", [&c, &m]() {
      const u16 rv = *rc::gen::arbitrary<u16>();

      c.bc = rv;
      inc_16<bc>(c, m);

      RC_ASSERT(c.bc == static_cast<u16>(rv + 1));
    });
    rc::prop("calling inc_16<de>", [&c, &m]() {
      const u16 rv = *rc::gen::arbitrary<u16>();

      c.de = rv;
      inc_16<de>(c, m);

      RC_ASSERT(c.de == static_cast<u16>(rv + 1));
    });
    rc::prop("calling inc_16<hl>", [&c, &m]() {
      const u16 rv = *rc::gen::arbitrary<u16>();

      c.hl = rv;
      inc_16<hl>(c, m);

      RC_ASSERT(c.hl == static_cast<u16>(rv + 1));
    });
    rc::prop("calling inc_16<sp>", [&c, &m]() {
      const u16 rv = *rc::gen::arbitrary<u16>();

      c.sp = rv;
      inc_16<sp>(c, m);

      RC_ASSERT(c.sp == static_cast<u16>(rv + 1));
    });
  }
}

SCENARIO("ld_at_16") {
  GIVEN("cpu, mmu") {
    cpu c;

    u8 bios_data[0x100] = {0};
    bios b{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{b, r};

    rc::prop("calling ld_at_16<bc>", [&c, &m]() {
      c.bc = *rc::gen::inRange<u16>(0xc000, 0xcfff);
      c.a = *rc::gen::arbitrary<u8>();

      ld_at_16<at_bc>(c, m);

      RC_ASSERT(m.read_u8(c.bc) == c.a);
    });
    rc::prop("calling ld_at_16<de>", [&c, &m]() {
      c.de = *rc::gen::inRange<u16>(0xc000, 0xcfff);
      c.a = *rc::gen::arbitrary<u8>();

      ld_at_16<at_de>(c, m);

      RC_ASSERT(m.read_u8(c.de) == c.a);
    });
  }
}

SCENARIO("ldi_at_hl") {
  GIVEN("cpu, mmu") {
    cpu c;

    u8 bios_data[0x100] = {0};
    bios b{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{b, r};

    rc::prop("calling ldi_at_16<bc>", [&c, &m]() {
      c.hl = *rc::gen::inRange<u16>(0xc001, 0xcfff - 2);
      c.a = *rc::gen::arbitrary<u8>();

      ldi_at_hl(c, m);

      RC_ASSERT(m.read_u8(c.hl - 1) == c.a);
    });
  }
}

SCENARIO("ldd_at_hl") {
  GIVEN("cpu, mmu") {
    cpu c;

    u8 bios_data[0x100] = {0};
    bios b{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{b, r};

    rc::prop("calling ldd_at_16<bc>", [&c, &m]() {
      c.hl = *rc::gen::inRange<u16>(0xc001, 0xcfff - 2);
      c.a = *rc::gen::arbitrary<u8>();

      ldd_at_hl(c, m);

      RC_ASSERT(m.read_u8(c.hl + 1) == c.a);
    });
  }
}

SCENARIO("bit n") {
  GIVEN("cpu, mmu") {
    cpu cpu_;

    u8 bios_data[0x100] = {0};
    bios bios_{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{bios_, r};

    rc::prop("calling bit<b, 7>", [&cpu_, &m]() {
      cpu_.b = *rc::gen::arbitrary<u8>();

      bit<b, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.b & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<c, 7>", [&cpu_, &m]() {
      cpu_.c = *rc::gen::arbitrary<u8>();

      bit<c, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.c & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<d, 7>", [&cpu_, &m]() {
      cpu_.d = *rc::gen::arbitrary<u8>();

      bit<d, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.d & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<e, 7>", [&cpu_, &m]() {
      cpu_.e = *rc::gen::arbitrary<u8>();

      bit<e, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.e & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<h, 7>", [&cpu_, &m]() {
      cpu_.h = *rc::gen::arbitrary<u8>();

      bit<h, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.h & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<l, 7>", [&cpu_, &m]() {
      cpu_.l = *rc::gen::arbitrary<u8>();

      bit<l, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.l & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<at_hl, 7>", [&cpu_, &m]() {
      const u8 rand_v = *rc::gen::arbitrary<u8>();
      cpu_.hl = *rc::gen::inRange<u16>(0xc000, 0xcfff);
      m.write_u8(cpu_.hl, rand_v);

      bit<at_hl, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(rand_v & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
    rc::prop("calling bit<a, 7>", [&cpu_, &m]() {
      cpu_.a = *rc::gen::arbitrary<u8>();

      bit<a, 7>(cpu_, m);

      RC_ASSERT(cpu_.zf == !!(cpu_.a & (1 << 7)));
      RC_ASSERT(cpu_.nf == false);
      RC_ASSERT(cpu_.hf == true);
    });
  }
}

SCENARIO("jr n") {
  GIVEN("cpu, mmu") {
    cpu cpu_;

    u8 bios_data[0x100] = {0};
    bios bios_{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{bios_, r};

    rc::prop("calling jr_n<zf>, zf = false", [&cpu_, &m]() {
      cpu_.pc = 0xc100;
      cpu_.zf = false;
      cpu_.im = *rc::gen::arbitrary<u8>();
      const i8 offset = cpu_.im;

      jr_n<zf>(cpu_, m);

      RC_ASSERT(cpu_.pc == (0xc100 + static_cast<i8>(cpu_.im) + 2));
    });
    rc::prop("calling jr_n<zf>, zf = true", [&cpu_, &m]() {
      cpu_.pc = 0xc100;
      cpu_.zf = true;
      cpu_.im = *rc::gen::arbitrary<u8>();
      const i8 offset = cpu_.im;

      jr_n<zf>(cpu_, m);

      RC_ASSERT(cpu_.pc == 0xc100 + 2);
    });
  }
}

SCENARIO("ld im") {
  GIVEN("cpu, mmu") {
    cpu cpu_;

    u8 bios_data[0x100] = {0};
    bios bios_{std::begin(bios_data)};
    u8 romonly_data[0x8000] = {0};
    romonly r{std::begin(romonly_data)};
    mmu m{bios_, r};

    rc::prop("calling ld_im<b>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<b>(cpu_, m);

      RC_ASSERT(cpu_.b == cpu_.im);
    });
    rc::prop("calling ld_im<c>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<c>(cpu_, m);

      RC_ASSERT(cpu_.c == cpu_.im);
    });
    rc::prop("calling ld_im<d>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<d>(cpu_, m);

      RC_ASSERT(cpu_.d == cpu_.im);
    });
    rc::prop("calling ld_im<e>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<e>(cpu_, m);

      RC_ASSERT(cpu_.e == cpu_.im);
    });
    rc::prop("calling ld_im<h>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<h>(cpu_, m);

      RC_ASSERT(cpu_.h == cpu_.im);
    });
    rc::prop("calling ld_im<l>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<l>(cpu_, m);

      RC_ASSERT(cpu_.l == cpu_.im);
    });
    rc::prop("calling ld_im<at_hl>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();
      cpu_.hl = *rc::gen::inRange<u16>(0xc000, 0xcfff - 1);

      ld_im<at_hl>(cpu_, m);

      RC_ASSERT(m.read_u8(cpu_.hl) == cpu_.im);
    });
    rc::prop("calling ld_im<a>", [&cpu_, &m]() {
      cpu_.im = *rc::gen::arbitrary<u8>();

      ld_im<a>(cpu_, m);

      RC_ASSERT(cpu_.a == cpu_.im);
    });
  }
}