#include "gdt.h"

extern void gdt_flushy(addr_t);

uint64_t gdt_entries[5];
struct gdt_ptr gdt_ptr;

void initgdt()
{
    gdt_ptr.size = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = &gdt_entries;

    gdt_entries[0] = 0x0;
    gdt_entries[1] = 0x00209A0000000000;
    gdt_entries[2] = 0x0000920000000000;
    gdt_entries[3] = 0x00affb000000ffff;
    gdt_entries[4] = 0x00aff3000000ffff;
    

    gdt_flushy(&gdt_ptr);

}

// void setgdtgate(uint32_t num, uint64_t base, uint32_t limit, uint8_t access, uint8_t gran)
// {

//     gdt_entries[num].base_lower = (base & 0xFFFF); // bit wise AND operation to ONLY get the 16 bits of the base
//     gdt_entries[num].base_middle = (base >> 16) & 0xFF; // bit wise shift to make it so the first 16 bits have the base, then we AND it and only get the first 16 bits
//     gdt_entries[num].base_higher = (base >> 24) & 0xFF; // same thing but we are just tryna get 8 bits instead

//     gdt_entries[num].limit = (limit & 0xFFFF); // bit mask to get the first 16 bits of limit
//     gdt_entries[num].flags = (limit >> 16) & 0x0F; // this is a lie, gdt_entries[num].flags is actually not just flags
//     // we have two things in this value
//     // 4 bit Flags value|4 bit Limit value
//     // so what we basically do is take the limit, shift it by 16 so we only get the first 16 bits and then we just AND it to get 4 bits and throw it in.
//     gdt_entries[num].flags |= (gran & 0xF0); 
//     // note A |= 9 is the same as A = A | 9
//     // so what we doing here is taking the 8 bit granilarity value and ANDing it with F0 to get the left 4 bits off it
//     // then we take all that shit and just OR it with flags so we get the granilarity value and the thing we just did with the limit value all together
//     // so we now have our final value
//     gdt_entries[num].access = access;

// }