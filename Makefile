CFLAGS+=-std=c11 -I include/ -MMD -MP -Wall -Wextra -pedantic -g
LDLIBS+=-ldl

all: src/damage src/lr35902.so test/test_main

test: test/test_main
	test/test_main

src/damage: src/damage.o src/cpu.o src/log.o src/types.o
test/test_main: test/test_main.o test/test_types.o src/types.o

src/lr35902.so: src/lr35902.o 
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ -fPIC -shared
src/lr35902.o: src/lr35902.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ -c -fPIC

.PHONY: clean
clean:
	rm -f src/damage
	rm -f src/*.o
	rm -f src/*.d
	rm -f src/*.so
	rm -f test/test_main
	rm -f test/*.o
	rm -f test/*.d
	rm -f test/*.so

-include $(wildcard src/*.d)
