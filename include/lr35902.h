#pragma once

#include "cpu.h"
#include "mmu.h"

template <typename Register>
void ld_imm(cpu &cpu_, mmu &mmu_, Register r = {}) {
  r.set(cpu_, mmu_, cpu_.imm);
  cpu_.cc += 12;
  cpu_.pc += 3;
}

template <typename Register> void xor_(cpu &cpu_, mmu &mmu_, Register r = {}) {
  cpu_.a ^= r.get(cpu_, mmu_);
  cpu_.zf = cpu_.a == 0;
  cpu_.nf = false;
  cpu_.hf = false;
  cpu_.cf = false;

  cpu_.cc += 3;
  cpu_.pc += 1;
}

template <typename Register>
void inc_16(cpu &cpu_, mmu &mmu_, Register r = {}) {
  r.set(cpu_, mmu_, r.get(cpu_, mmu_) + 1);
}