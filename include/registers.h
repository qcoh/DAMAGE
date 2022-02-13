#pragma once

// type level accessors for the registers. See lr35902.h how these are used.
struct a {
  u8 get(cpu &cpu_, mmu &) { return cpu_.a; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.a = v; }
};
struct f {
  u8 get(cpu &cpu_, mmu &) { return cpu_.f; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.f = v; }
};
struct b {
  u8 get(cpu &cpu_, mmu &) { return cpu_.b; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.b = v; }
};
struct c {
  u8 get(cpu &cpu_, mmu &) { return cpu_.c; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.c = v; }
};
struct d {
  u8 get(cpu &cpu_, mmu &) { return cpu_.d; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.d = v; }
};
struct e {
  u8 get(cpu &cpu_, mmu &) { return cpu_.e; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.e = v; }
};
struct h {
  u8 get(cpu &cpu_, mmu &) { return cpu_.h; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.h = v; }
};
struct l {
  u8 get(cpu &cpu_, mmu &) { return cpu_.l; }
  void set(cpu &cpu_, mmu &, u8 v) { cpu_.l = v; }
};

struct af {
  u16 get(cpu &cpu_, mmu &) { return cpu_.af; }
  void set(cpu &cpu_, mmu &, u16 v) { cpu_.af = v; }
};
struct bc {
  u16 get(cpu &cpu_, mmu &) { return cpu_.bc; }
  void set(cpu &cpu_, mmu &, u16 v) { cpu_.bc = v; }
};
struct de {
  u16 get(cpu &cpu_, mmu &) { return cpu_.de; }
  void set(cpu &cpu_, mmu &, u16 v) { cpu_.de = v; }
};
struct hl {
  u16 get(cpu &cpu_, mmu &) { return cpu_.hl; }
  void set(cpu &cpu_, mmu &, u16 v) { cpu_.hl = v; }
};
struct sp {
  u16 get(cpu &cpu_, mmu &) { return cpu_.sp; }
  void set(cpu &cpu_, mmu &, u16 v) { cpu_.sp = v; }
};

struct at_hl {
  u8 get(cpu &cpu_, mmu &mmu_) { return mmu_.read_u8(cpu_.hl); }
  void set(cpu &cpu_, mmu &mmu_, u8 v) { mmu_.write_u8(cpu_.hl, v); }
};