#pragma once

#include "mapper.h"
#include "types.h"

#include <algorithm>
#include <iterator>

// romonly is a mapper that exposes 32768 bytes without bank switching.
struct romonly : public mapper {
  template <class InputIterator> romonly(InputIterator input_iterator) {
    std::copy_n(input_iterator, rom_size, std::begin(data));
  }

  u8 read_u8(u16);
  void write_u8(u16, u8);

  static constexpr u16 rom_size = 0x8000;
  u8 data[rom_size];
};