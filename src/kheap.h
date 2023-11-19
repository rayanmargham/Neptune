#ifndef _NEPTUNE_KHEAP_H_
#define _NEPTUNE_KHEAP_H_
#include "stddef.h"
void kheap_init();
void free(void *uhoh);
void *malloc(size_t size);
void *realloc(void *old_guy, size_t new_size);
#endif