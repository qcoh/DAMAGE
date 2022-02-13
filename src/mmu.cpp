#include "mmu.h"
#include "bios.h"
#include "mapper.h"

mmu::mmu(bios &bios_, mapper &mapper_) : m_bios{bios_}, m_mapper{mapper_} {}

u8 mmu::read_u8(u16 address) {
  if (address == 0x100) {
    m_strategy = &mmu::read_u8_with_cart;
  }

  if (0x0 <= address && address < 0x100) {
    return (this->*m_strategy)(address);
  } else if (0x100 <= address && address <= 0x3fff) {
    return m_mapper.read_u8(address);
  } else if (0xc000 <= address && address <= 0xcfff) {
    return wram[address - 0xc000];
  } else if (0xff00 <= address && address < 0xffff) {
    return hram[address - 0xff00];
  }
  return 0;
}
void mmu::write_u8(u16 address, u8 v) {
  if (0x0 <= address && address < 0x3fff) {
    m_mapper.write_u8(address, v);
  } else if (0xc000 <= address && address < 0xcfff) {
    wram[address - 0xc000] = v;
  } else if (0xff00 <= address && address < 0xffff) {
    hram[address - 0xff00] = v;
  }
}

u8 mmu::read_u8_with_bios(u16 address) { return m_bios.read_u8(address); }
u8 mmu::read_u8_with_cart(u16 address) { return m_mapper.read_u8(address); }
