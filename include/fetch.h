#pragma once

// fetch.h contains the code responsible for monitoring lr35902.so
// and (re)loading instructions from it.

#include "types.h"

struct fetcher {
	void *handle;
	void *fetch_function;
	
	int inotify_fd;
	int watch_fd;
	char filename[16];
};

struct fetcher new_fetcher(const char *, const char *);
void shutdown_fetcher(struct fetcher *);

struct instruction;
struct instruction fetch(struct fetcher*, u8);
