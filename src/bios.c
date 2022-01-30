#include "bios.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

struct bios new_bios(const char *filename) {
	struct bios ret = {0};

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		error("fopen:");
		exit(EXIT_FAILURE);
	}

	size_t bios_size = fread(ret.data, 1, 256, fp);
	if (bios_size != 256) {
		error("BIOS has unexpected size: %d != 256\n", bios_size);
		exit(EXIT_FAILURE);
	}

	return ret;
}
