#pragma once

// types.h comprises the primitive types used throughout: typedefs for
// integer types and a register type.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned short u32;

struct reg {
	u8 hi;
	u8 lo;
};

void set_reg(struct reg *, u16);
u16 get_word(struct reg);
