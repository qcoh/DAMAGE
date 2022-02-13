#pragma once

#include "memory.h"
#include "types.h"

struct mapper : public memory<mapper> {
  mapper() = default;
  virtual ~mapper() = default;

  mapper(const mapper &) = delete;
  mapper &operator=(const mapper &) = delete;
  mapper(mapper &&) = delete;
  mapper &operator=(mapper &&) = delete;

  virtual u8 read_u8(u16) = 0;
  virtual void write_u8(u16, u8) = 0;
};