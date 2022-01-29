#pragma once

// types.h comprises the primitive types used throughout: typedefs for
// integer types and a register type.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned short u32;

typedef struct {
	u8 hi;
	u8 lo;
} reg;

// I prefer using bitshifting over unions to keep the code portable. When
// compiling with -O2, the function calls and bit operations are optimized
// to simple movs. See extras/union_code.c.
inline void set_reg(reg *r, u16 v) { r->hi = v >> 8; r->lo = v & 0xff; }
inline u16 get_word(reg r) { return r.hi << 8 | r.lo; }
