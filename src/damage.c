#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "lr35902.h"

#define INSTRUCTIONS_SHARED_LIBRARY "lr35902.so"
#define FETCH_FUNCTION_NAME "fetch"

int main() {
	void *instructions = dlopen(INSTRUCTIONS_SHARED_LIBRARY, RTLD_LAZY);
	if (!instructions) {
		fprintf(stderr, "Unable to load %s\n", INSTRUCTIONS_SHARED_LIBRARY);
		return EXIT_FAILURE;
	}

	fetch_function fetch;
       	*(void **)(&fetch) = dlsym(instructions, FETCH_FUNCTION_NAME);
	if (!fetch) {
		fprintf(stderr, "Unable to load symbol %s\n", FETCH_FUNCTION_NAME);
		return EXIT_FAILURE;
	}

	printf("Successfully loaded %s\n", FETCH_FUNCTION_NAME);

	struct instruction test = fetch(0);
	printf("test.opcode == %x\n", test.opcode);

	return 0;
}
