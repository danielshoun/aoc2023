#ifndef COMPAT_H
#define COMPAT_H
#include <stdio.h>
#include <errno.h>

#ifdef __APPLE_CC__
errno_t fopen_s(FILE**, char*, char*);
void strcpy_s(char*, size_t, char*);
#endif

#endif //COMPAT_H
