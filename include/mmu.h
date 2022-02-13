#pragma once

#include "memory.h"
#include "types.h"

struct mmu : public memory<mmu> {
  u8 read_u8(u16);
  void write_u8(u16, u8);
};