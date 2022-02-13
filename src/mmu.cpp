#include "mmu.h"

u8 mmu::read_u8(u16) noexcept { return 0; }
u16 mmu::read_u16(u16) noexcept { return 0; }
void mmu::write_u8(u16, u8) noexcept {}
void mmu::write_u16(u16, u16) noexcept {}