#include "include/helpers.h"

size_t strlen(const char *s) {
    size_t n = 0;
    if (!s) return 0;
    while (*s++) n++;
    return n;
}

int strcmp(const char *a, const char *b) {
    const unsigned char *pa = (const unsigned char*)a;
    const unsigned char *pb = (const unsigned char*)b;
    while (*pa && (*pa == *pb)) { pa++; pb++; }
    return (int)(*pa) - (int)(*pb);
}
