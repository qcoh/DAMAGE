#include "types.h"

// I prefer using bitshifting over unions to keep the code portable. When
// compiling with -O2, the function calls and bit operations are optimized
// to simple movs. See extras/union_code.c.
void set_reg(struct reg *r, u16 v) {
	r->hi = v >> 8;
	r->lo = v & 0xff;
}

u16 get_word(struct reg r) {
	return r.hi << 8 | r.lo;
}
