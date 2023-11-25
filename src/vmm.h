#ifndef _VMM_H_
#define _VMM_H_
#include "stdint.h"
void vmm_init();
void map(uint64_t *pml4, uintptr_t virt_addr, uintptr_t phys_addr, uint64_t flags);
#endif