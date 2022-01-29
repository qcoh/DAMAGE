#include "cpu.h"
#include "mmu.h"

// step performs a single emulation step. It
//
// * fetches the next instruction from the mmu at the program counter
// * executes the instruction (modifying the cpu's state and mmu contents)
// * increases the cycle counter
// * advances the program counter (or does a call/jump)
void step(struct cpu *c, struct mmu *m) {
	(void)c;
	(void)m;
}
