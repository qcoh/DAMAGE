#pragma once

#include "types.h"

struct cpu;
struct mmu;
typedef void (*instruction_function)(struct cpu *, struct mmu *);

struct instruction {
	u8 opcode;
	u8 length;
	u8 cycles;
	instruction_function fp;
};

typedef struct instruction (*fetch_function)(u8);
