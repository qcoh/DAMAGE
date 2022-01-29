CPPFLAGS = -std=c11 -Wall -Wextra -pedantic -g -O2
LDFLAGS += 

all: union_code inotify
union_code: union_code.o
inotify: inotify.o

.PHONY: clean
clean:
	rm -f union_code
	rm -f src/*.o
