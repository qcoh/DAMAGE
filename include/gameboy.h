#pragma once

struct cpu;
struct mmu;

struct gameboy {
  explicit gameboy(cpu &, mmu &);

  void step();

  cpu &m_cpu;
  mmu &m_mmu;

  bool stopped = false;
};