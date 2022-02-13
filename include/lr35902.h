#pragma once

#include "cpu.h"
#include "mmu.h"

template <typename Register, class Cpu, class Mmu>
void ld_imm(Cpu &cpu_, Mmu &) {
  Register r;
  r(cpu_) = cpu_.imm;
  cpu_.cc += 12;
  cpu_.pc += 3;
}