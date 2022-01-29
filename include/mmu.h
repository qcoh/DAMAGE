#pragma once

// mmu.h comprises the definition and helper functions for the mmu.

#include "types.h"

struct mmu {
	u8 nothing;
};

inline u8 read_byte(struct mmu *m, u16 address) { (void)m; (void)address; return 0; }
inline u16 read_word(struct mmu *m, u16 address) { (void)m; (void)address; return 0; }
inline void write_byte(struct mmu *m, u16 address, u8 b) { (void)m; (void)address; (void)b; }
inline void write_word(struct mmu *m, u16 address, u16 w) { (void)m; (void)address; (void)w; }
