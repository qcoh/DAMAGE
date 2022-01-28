CFLAGS+=-std=c11 -I include/ -MMD -MP -Wall -Wextra -pedantic -g
LDFLAGS+=

src/damage: src/damage.o

.PHONY: clean
clean:
	rm -f src/damage
	rm -f src/*.o
	rm -f src/*.d

-include $(wildcard src/*.d)
