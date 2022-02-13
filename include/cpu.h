#pragma once

#include "types.h"
#include "word.h"

// cpu comprises 8bit registers, 16bit registers, the stack pointer,
// the program counter and the cycle counter.
struct cpu {
  u8 a{0};
  u8 f{0};
  u8 b{0};
  u8 c{0};
  u8 d{0};
  u8 e{0};
  u8 h{0};
  u8 l{0};

  word af{a, f};
  word bc{b, c};
  word de{d, e};
  word hl{h, l};

  u16 sp{0xffff};
  u16 pc{0};
  u32 cc{0};

  u8 im{0};
  u16 imm{0};
};

// type level accessors for the registers. See lr35902.h how these are used.
struct a {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.a; }
};
struct f {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.f; }
};
struct b {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.b; }
};
struct c {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.c; }
};
struct d {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.d; }
};
struct e {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.e; }
};
struct h {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.h; }
};
struct l {
  u8 &operator()(cpu &cpu_) noexcept { return cpu_.l; }
};

struct af {
  word &operator()(cpu &cpu_) noexcept { return cpu_.af; }
};
struct bc {
  word &operator()(cpu &cpu_) noexcept { return cpu_.bc; }
};
struct de {
  word &operator()(cpu &cpu_) noexcept { return cpu_.de; }
};
struct hl {
  word &operator()(cpu &cpu_) noexcept { return cpu_.hl; }
};
struct sp {
  u16 &operator()(cpu &cpu_) noexcept { return cpu_.sp; }
};