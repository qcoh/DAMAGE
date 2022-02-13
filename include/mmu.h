#pragma once

#include "memory.h"
#include "types.h"

struct bios;
struct mapper;

struct mmu : public memory<mmu> {
  explicit mmu(bios &, mapper &);

  u8 read_u8(u16);
  void write_u8(u16, u8);

  bios &m_bios;
  mapper &m_mapper;

  u8 wram[0x1000];
  u8 hram[0x80];

private:
  // When the GameBoy starts, the bios is mapped to the region [0x0, 0x100).
  // Once the program counter hits 0x100, the cartridge/mapper is mapped to that
  // region.
  //
  // We use two implementations for reading from this region and toggle them as
  // soon as a value is read at 0x100.
  u8 read_u8_with_bios(u16);
  u8 read_u8_with_cart(u16);

  using mmu_strategy_type = u8 (mmu::*)(u16);
  mmu_strategy_type m_strategy = &mmu::read_u8_with_bios;
};