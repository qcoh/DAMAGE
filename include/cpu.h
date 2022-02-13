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
};
