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
  } else if (0x100 <= address && address < 0x3fff) {
    return m_mapper.read_u8(address);
  }
  return 0;
}
void mmu::write_u8(u16, u8) {}

u8 mmu::read_u8_with_bios(u16 address) { return m_bios.read_u8(address); }
u8 mmu::read_u8_with_cart(u16 address) { return m_mapper.read_u8(address); }
