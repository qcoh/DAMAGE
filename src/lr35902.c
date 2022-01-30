#include "lr35902.h"
#include "cpu.h"
#include "mmu.h"

void nop(struct cpu *c, struct mmu *m) { (void)c; (void)m; return; }

struct instruction instructions[0x100] = {
	{0x00, 1, 4, nop},
	{0x01, 1, 4, nop},
};

struct instruction fetch(u8 opcode) {
	return instructions[opcode];
}
