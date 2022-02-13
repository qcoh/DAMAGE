#pragma once

#include "cpu.h"
#include "mmu.h"
#include "registers.h"

#include <type_traits>

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

  cpu_.cc += 4;
  if constexpr (std::is_same<Register, at_hl>::value) {
    cpu_.cc += 4;
  }

  cpu_.pc += 1;
}

template <typename Register>
void inc_16(cpu &cpu_, mmu &mmu_, Register r = {}) {
  r.set(cpu_, mmu_, r.get(cpu_, mmu_) + 1);

  cpu_.cc += 8;
  cpu_.pc += 1;
}

template <typename Register>
void ld_at_16(cpu &cpu_, mmu &mmu_, Register r = {}) {
  r.set(cpu_, mmu_, cpu_.a);

  cpu_.cc += 8;
  cpu_.pc += 1;
}

void ldi_at_hl(cpu &cpu_, mmu &mmu_) {
  mmu_.write_u8(cpu_.hl, cpu_.a);
  cpu_.hl = cpu_.hl + 1;

  cpu_.cc += 8;
  cpu_.pc += 1;
}

void ldd_at_hl(cpu &cpu_, mmu &mmu_) {
  mmu_.write_u8(cpu_.hl, cpu_.a);
  cpu_.hl = cpu_.hl - 1;

  cpu_.cc += 8;
  cpu_.pc += 1;
}

template <typename Register, int I>
void bit(cpu &cpu_, mmu &mmu_, Register r = {}) {
  cpu_.zf = r.get(cpu_, mmu_) & (1 << I);
  cpu_.nf = false;
  cpu_.hf = true;

  cpu_.cc += 8;
  if constexpr (std::is_same<Register, at_hl>::value) {
    cpu_.cc += 8;
  }
  cpu_.pc += 2;
}

template <typename Register> void jr_n(cpu &cpu_, mmu &mmu_, Register r = {}) {
  if (!r.get(cpu_, mmu_)) {
    cpu_.pc += static_cast<i8>(cpu_.im);
    cpu_.cc += 4;
  }
  cpu_.cc += 8;
  cpu_.pc += 2;
}

template <typename Register> void ld_im(cpu &cpu_, mmu &mmu_, Register r = {}) {
  r.set(cpu_, mmu_, cpu_.im);

  if constexpr (std::is_same<Register, at_hl>::value) {
    cpu_.cc += 4;
  }
  cpu_.cc += 8;
  cpu_.pc += 2;
}

void ld_at_c(cpu &cpu_, mmu &mmu_) {
  mmu_.write_u8(0xff00 + cpu_.c, cpu_.a);
  cpu_.cc += 8;
  cpu_.pc += 2;
}

template <typename Dst, typename Src>
void ld(cpu &cpu_, mmu &mmu_, Dst dst = {}, Src src = {}) {
  dst.set(cpu_, mmu_, src.get(cpu_, mmu_));

  if constexpr (std::is_same<Dst, at_hl>::value ||
                std::is_same<Src, at_hl>::value) {
    cpu_.cc += 4;
  }

  cpu_.cc += 4;
  cpu_.pc += 1;
}