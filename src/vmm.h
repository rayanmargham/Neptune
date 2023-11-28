#ifndef _VMM_H_
#define _VMM_H_
#include "stdint.h"
#include "stddef.h"
uint64_t align_up(uint64_t addr, size_t page_size);
uint64_t align_down(uint64_t addr, size_t page_size);
void vmm_init();
void map(uint64_t *pml4, uintptr_t virt_addr, uintptr_t phys_addr, uint64_t flags);
void *vmm_alloc(int pages);
void vmm_free(void *base);
#endif