#include <stdio.h>
#include <stdlib.h>

#include "lr35902.h"
#include "log.h"
#include "fetch.h"

int main() {
	struct fetcher fetcher = new_fetcher("/home/jerry/Coding/DAMAGE/src", "lr35902.so");

	struct instruction foo = fetch(&fetcher, 0x01);

	return 0;
}
