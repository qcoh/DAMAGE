#include <stdio.h>

// Here, we want to check if type ereasure with unions produces
// (much) better code, compared with using bitshifting and masks.
// Both are legal in C but not in C++, as far as I know.

typedef unsigned char u8;
typedef unsigned short u16;

typedef union {
	u16 word;
	struct {
		u8 hi;
		u8 lo;
	};
} reg;

typedef struct {
	u8 hi;
	u8 lo;
} reg_shift;

void set_reg(reg_shift *r, u16 v) { r->lo = v >> 8; r->hi = v & 0xff; }

int main() {
	reg r = {0};
	r.word = 0x1234;
	printf("%x %x\n", r.hi, r.lo);

	reg_shift rs = {0};
	set_reg(&rs, 0x1234);
	printf("%x %x\n", rs.hi, rs.lo);

	return 0;
}
