#include "fetch.h"
#include "lr35902.h"
#include "log.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/inotify.h>
#include <dlfcn.h>

void load(struct fetcher *fetcher, const char *filename) {
	if ((fetcher->handle = dlopen(filename, RTLD_LAZY)) == NULL) {
		critical("dlopen: %s", dlerror());
		exit(EXIT_FAILURE);
	}

	if ((fetcher->fetch_function = dlsym(fetcher->handle, "fetch")) == NULL) {
		critical("dlsym:");
		exit(EXIT_FAILURE);
	}
}

int reload(struct fetcher *fetcher) {
	char buf[10 * (sizeof(struct inotify_event) + 16 + 1)];

	debug("reading from inotify\n");

	// blocks!
	int bytes_read = read(fetcher->inotify_fd, buf, sizeof(buf));
	if (bytes_read == 0) {
		critical("read 0 bytes");
		exit(EXIT_FAILURE);
	}
	if (bytes_read == -1) {
		critical("read:");
		exit(EXIT_FAILURE);
	}

	struct inotify_event *ev;
	for (char *ptr = buf; ptr < buf + bytes_read; ptr += sizeof(struct inotify_event) + ev->len) {
		ev = (struct inotify_event*)ptr;
		if (ev->mask & IN_IGNORED) {
			critical("file was removed from inotify watch");
			exit(EXIT_FAILURE);
		}

		debug("Inotify event: %s\n", ev->name, ev->mask);
		if (ev->mask & IN_CLOSE) {
			debug("IN_CLOSE\n");
		}

		const int library_ready = 
			(ev->mask & IN_CLOSE_WRITE) && (strncmp(ev->name, fetcher->filename, 16) == 0);

		if (library_ready) {
			dlclose(fetcher->handle);
			debug("Loading %s\n", fetcher->filename);
			load(fetcher, fetcher->filename);
			return 1;
		}
	}

	return 0;
}

struct fetcher new_fetcher(const char *directory, const char *filename) {
	struct fetcher ret = {0};
	strncpy(ret.filename, filename, sizeof(ret.filename));

	if ((ret.inotify_fd = inotify_init1(IN_CLOEXEC)) == -1) {
		critical("inotify_init1");
		exit(EXIT_FAILURE);
	}

	if ((ret.watch_fd = inotify_add_watch(ret.inotify_fd, directory, IN_CLOSE_WRITE)) == -1) {
		critical("inotify_add_watch");
		exit(EXIT_FAILURE);
	}

	load(&ret, filename);

	return ret;
}

struct instruction fetch(struct fetcher *fetcher, u8 opcode) {
	struct instruction ret = {0};

	while (ret.fp == NULL) {
		fetch_function f;
		*(void **)(&f) = fetcher->fetch_function;
		ret = f(opcode);

		if (ret.fp == NULL) {
			info("Instruction %x not implemented\n", opcode);
			reload(fetcher);
		}
	}

	return ret;
}
