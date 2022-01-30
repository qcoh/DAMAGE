#pragma once

#include <stdio.h>

#define debug(...) log_impl(stdout, "DEBUG", "\x1B[39m", __FILE__, __LINE__, __VA_ARGS__)
#define info(...) log_impl(stdout, "INFO", "\x1B[34m", __FILE__, __LINE__, __VA_ARGS__)
#define notice(...) log_impl(stdout, "NOTICE", "\x1B[32m", __FILE__, __LINE__, __VA_ARGS__)
#define warning(...) log_impl(stdout, "WARNING", "\x1B[33m",  __FILE__, __LINE__, __VA_ARGS__)
#define error(...) log_impl(stderr, "ERROR", "\x1B[31m", __FILE__, __LINE__, __VA_ARGS__)
#define critical(...) log_impl(stderr, "CRITICAL", "\x1B[37;41m", __FILE__, __LINE__, __VA_ARGS__)

int log_impl(FILE *, const char *, const char *, const char *, long, const char *, ...);
