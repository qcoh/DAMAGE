#pragma once

#include "types.h"

struct cpu;
struct mmu;

struct gameboy {
  explicit gameboy(cpu &, mmu &);

  void step();

  void regular_step(u8);
  void extended_step(u8);

  cpu &m_cpu;
  mmu &m_mmu;

  bool stopped = false;
};