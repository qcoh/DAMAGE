#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

int log_impl(FILE *stream, const char *type, const char *color, const char *file, long line, const char *fmt, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);

	if (fmt[strlen(fmt) - 1] == ':') {
		return fprintf(stream, "%s[%s]\t\t%s:%ld:\t%s %s\x1B[0\n", color, type, file, line, buffer,strerror(errno));
	}
	return fprintf(stream, "%s[%s]\t\t%s:%ld:\t%s\x1B[0", color, type, file, line, buffer);
}

