#include <stdint.h>
#ifndef _GDT_H_
#define _GDT_H_
struct gdt_entry
{
    uint16_t limit;
    uint16_t base_lower;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_higher;
} __attribute__((packed));

struct gdt_ptr
{
    uint16_t size;
    uint64_t base;
} __attribute__((packed));

void initgdt();
void setgdtgate(uint32_t num, uint64_t base, uint32_t limit, uint8_t access, uint8_t gran);
#endif