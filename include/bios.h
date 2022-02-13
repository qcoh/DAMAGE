#pragma once

#include "types.h"

#include <algorithm>
#include <iterator>

// bios reads a bios file and provides its contents.
struct bios {
  static constexpr u16 data_size = 0x100;

  template <class InputIterator> explicit bios(InputIterator first) {
    std::copy_n(first, data_size, std::begin(data));
  }

  u8 read_u8(u16);
  u8 data[data_size];
};