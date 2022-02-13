#pragma once

#include "types.h"

// memory provides the ability to read and write words in terms of bytes.
template <class ReadWriter> struct memory {
  u16 read_u16(u16 address) {
    auto &derived = static_cast<ReadWriter &>(*this);
    return derived.read_u8(address) | (derived.read_u8(address + 1) << 8);
  }

  void write_u16(u16 address, u16 value) {
    auto &derived = static_cast<ReadWriter &>(*this);
    derived.write_u8(address, static_cast<u8>(value));
    derived.write_u8(address + 1, static_cast<u8>(value >> 8));
  }
};