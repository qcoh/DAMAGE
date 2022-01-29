#include "log.h"

#include <stdio.h>
#include <stdarg.h>

int debug(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stdout, "\x1B[39m[DEBUG]\t%s\x1B[0", buffer);
}

int info(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stdout, "\x1B[34m[INFO]\t%s\x1B[0", buffer);
}

int notice(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stdout, "\x1B[32m[NOTICE]\t%s\x1B[0", buffer);
}

int warning(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stdout, "\x1B[33m[WARNING]\t%s\x1B[0", buffer);
}

int error(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stderr, "\x1B[31m[ERROR]\t%s\x1B[0", buffer);
}

int critical(const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	return fprintf(stderr, "\x1B[37;41m[CRITICAL]\t%s\x1B[0", buffer);
}
