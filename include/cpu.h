#pragma once

// cpu.h comprises the definition of the cpu's state: the registers,
// the stack pointer, the program counter and the cycle counter.

#include "types.h"

struct cpu {
	u32 cc;

	u16 sp;
	u16 pc;

	struct reg af;
	struct reg bc;
	struct reg de;
	struct reg hl;
};

#define REG_A(r) (r).af.hi
#define REG_F(r) (r).af.lo
#define REG_B(r) (r).bc.hi
#define REG_C(r) (r).bc.lo
#define REG_D(r) (r).de.hi
#define REG_E(r) (r).de.lo
#define REG_H(r) (r).hl.hi
#define REG_L(r) (r).hl.lo

struct mmu;

void step(struct cpu *, struct mmu *);
