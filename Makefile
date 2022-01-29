CFLAGS+=-std=c11 -I include/ -MMD -MP -Wall -Wextra -pedantic -g
LDFLAGS+=

all: src/damage src/lr35902.so
src/damage: src/damage.o src/cpu.o

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

-include $(wildcard src/*.d)
