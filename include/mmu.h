#pragma once

#include "types.h"

struct mmu {
  u8 read_u8(u16) noexcept;
  u16 read_u16(u16) noexcept;
  void write_u8(u16, u8) noexcept;
  void write_u16(u16, u16) noexcept;
};