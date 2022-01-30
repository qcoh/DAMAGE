#pragma once

#include "types.h"

struct bios {
	u8 data[0x100];
};

struct bios new_bios(const char *);
