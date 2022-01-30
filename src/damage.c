#include <stdio.h>
#include <stdlib.h>

#include "lr35902.h"
#include "log.h"
#include "fetch.h"
#include "bios.h"

int main(int argc, char *argv[]) {
	struct bios bios = new_bios(argv[1]);

	struct fetcher fetcher = new_fetcher("/home/jerry/Coding/DAMAGE/src", "lr35902.so");

	struct instruction foo = fetch(&fetcher, 0x01);

	shutdown_fetcher(&fetcher);

	return 0;
}
