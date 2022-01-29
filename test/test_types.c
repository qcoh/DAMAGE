#include "utest.h"

#include "types.h"

UTEST(reg, get_set_identity) {
	struct reg r;
	set_reg(&r, 0x1234);
	ASSERT_EQ(get_word(r), 0x1234);
}
