#include "cpu.h"
#include "mmu.h"

// step performs a single emulation step. It
//
// * fetches the next instruction from the mmu at the program counter
// * executes the instruction (modifying the cpu's state and mmu contents)
// * increases the cycle counter
// * advances the program counter (or does a call/jump)
void step(struct cpu *c, struct mmu *m) {
	const u8 opcode = read_byte(m, c->pc);

	u8 length = 0;
	u8 cycles = 0;

	switch (opcode) {
	case 0x00: {
		length += 1;
		cycles += 4;
	}
	default: break;
	}

	c->pc += length;
	c->cc += cycles;
}
