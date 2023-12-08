#ifndef COMPAT_H
#define COMPAT_H
#include <stdio.h>
#include <errno.h>

#ifdef __APPLE_CC__
errno_t fopen_s(FILE**, char*, char*);
void strcpy_s(char*, size_t, char*);
#endif

#ifdef WIN32
#include <stdint.h>
#endif

#endif //COMPAT_H
