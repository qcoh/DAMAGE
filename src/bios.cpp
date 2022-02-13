#include "bios.h"

#include <stdexcept>

u8 bios::read_u8(u16 address) {
  if (address >= bios::data_size) {
    throw std::runtime_error{"trying to read from bios with address >= 0x100!"};
  }
  return data[address];
}