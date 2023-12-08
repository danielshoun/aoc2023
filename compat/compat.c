#ifdef __APPLE_CC__

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/_types/_errno_t.h>

errno_t fopen_s(FILE** f, const char* name, const char* mode) {
    errno_t ret = 0;
    assert(f);
    *f = fopen(name, mode);
    if (!*f)
        ret = errno;
    return ret;
}

void strcpy_s(char* dest, size_t _, char* src) {
    strcpy(dest, src);
}

#endif