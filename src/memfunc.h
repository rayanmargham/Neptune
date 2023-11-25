#ifndef MEMFUNC_H_
#define MEMFUNC_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
const char* to_hstring(uint64_t value);
const char *to_string(uint64_t value);
int strlen(const char *msg);
int strncmp(const char* s1, const char* s2, size_t n);
#endif