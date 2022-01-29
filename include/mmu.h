#pragma once

// mmu.h comprises the definition and helper functions for the mmu.

#include "types.h"

struct mmu {
	u8 nothing;
};

u8 read_byte(struct mmu *m, u16 address) { (void)m; (void)address; return 0; }
u16 read_word(struct mmu *m, u16 address) { (void)m; (void)address; return 0; }
void write_byte(struct mmu *m, u16 address, u8 b) { (void)m; (void)address; (void)b; }
void write_word(struct mmu *m, u16 address, u16 w) { (void)m; (void)address; (void)w; }
