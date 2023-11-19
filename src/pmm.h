#ifndef _PMM_H_
#define _PMM_H_
#include <stdint.h>
#include <stddef.h>
void *pmm_alloc_singlep();
void pmm_dealloc_singlep(void *page);
void pmm_init();
#endif