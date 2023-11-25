#include "vmm.h"
#include "pmm.h"
#include "memfunc.h"
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "kheap.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
extern volatile struct limine_hhdm_request hhdm_request;
extern char THE_REAL[];
struct limine_kernel_address_request addr_request = 
{
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 1
};
struct vmm_memory_region
{
    uint64_t base;
    uint64_t length;
    uint64_t flags;
    struct vmm_memory_region *next;
};
struct vmm_memory_region *head;
void vmm_alloc(int pages)
{
    if (!head)
    {
        head = malloc(sizeof(struct vmm_memory_region));
        head->base = hhdm_request.response->offset;
        for (int i = 0; i > pages; i++)
        {

        }
    }
}
#define _SATURN_PRESENT_BITMASK 0x1
#define _SATURN_READWRITE_BITMASK 0x2
void update_cr3(uint64_t cr3_value)
{
    __asm__ volatile("mov %0, %%cr3" :: "r"((uint64_t)cr3_value) : "memory");
}
uint64_t *read_cr3()
{
    uint64_t cr3;
    __asm__ volatile ("mov %%cr3, %0" : "=r"(cr3) :: "memory");
    return cr3 + hhdm_request.response->offset;
}
uint64_t align_down(uint64_t addr, size_t page_size)
{
    return addr & ~(page_size - 1);
}
uint64_t align_up(uint64_t addr, size_t page_size)
{
    return (addr + (page_size - 1)) & ~(page_size - 1);
}
void REAL_update_cr3(uint64_t *pml4_address)
{

    uint64_t aligned_addr = align_down((uint64_t)pml4_address, 4096);

    kflantprint(ft_ctx, to_hstring(aligned_addr - hhdm_request.response->offset), 64, 0xFFFFF, "Virtual Memory Manager", 23, true);


    update_cr3(aligned_addr - hhdm_request.response->offset);

}


uint64_t *get_next_lvl(uint64_t *table, uint64_t index)
{
    if ((table[index] & _SATURN_PRESENT_BITMASK) == 0)
    {
        // table indexxed does not exist, allocate that shit
        uint64_t *new_table = pmm_alloc_singlep(); // pmm returns phys addr

        memset((uint64_t)new_table + hhdm_request.response->offset, 0, 4096);

        uint64_t entry = 0;
        entry = entry | (uint64_t)new_table;

        entry = entry | _SATURN_PRESENT_BITMASK;
        entry = entry | _SATURN_READWRITE_BITMASK;
        
        table[index] = entry;
        return (table[index] & 0x000FFFFFFFFFF000);
    }
    else
    {
        return (table[index] & 0x000FFFFFFFFFF000);
    }
}

void map(uint64_t *pml4, uintptr_t virt_addr, uintptr_t phys_addr, uint64_t flags)
{
    uint64_t lvl4_index = (virt_addr >> 39) & 0x1FF; // SHOULD BE ROOT PAGE TABLE (PML4)
    uint64_t lvl3_index = (virt_addr >> 30) & 0x1FF; // SHOULD BE PAGE POINTER DESCRIPTOR
    uint64_t lvl2_index = (virt_addr >> 21) & 0x1FF; // SHOULD BE PAGE DESCRIPTOR
    uint64_t lvl1_index = (virt_addr >> 12) & 0x1FF; // SHOULD BE PAGE TABLE
    
    uint64_t *cur_table;
    cur_table = get_next_lvl(pml4, lvl4_index);
    cur_table = get_next_lvl((uint64_t)cur_table + hhdm_request.response->offset, lvl3_index);
    cur_table = get_next_lvl((uint64_t)cur_table + hhdm_request.response->offset, lvl2_index);
    // we've gotten the page table, now we give the phys address and whatever tf
    uint64_t entry = 0;

    entry = entry | (uint64_t) phys_addr;
    entry = entry | _SATURN_PRESENT_BITMASK;
    entry = entry | _SATURN_READWRITE_BITMASK;
    // the funny!
    ((uint64_t*)((uint64_t)cur_table + hhdm_request.response->offset))[lvl1_index] = entry;
}
uint64_t *pml4;
void vmm_init()
{
    size_t kernel_size_in_bytes = (size_t)THE_REAL;
    kernel_size_in_bytes = align_up(kernel_size_in_bytes, 4096);
    uint64_t kernel_virt_addr_base = addr_request.response->virtual_base;
    uint64_t kernel_phys_addr_base = addr_request.response->physical_base;
    pml4 = pmm_alloc_singlep(); // returns a physical addr + higher half offset
    memset(((uint64_t)pml4 + hhdm_request.response->offset), 0, 4096); // zero out the root page table (pml4)
    // now we map kernel
    // wait i should align the kernel size in bytes into a page
    uint64_t *old_map = read_cr3();
    for (int i = 256; i < 512; i++)
    {
        ((uint64_t*)((uint64_t)pml4 + hhdm_request.response->offset))[i] = old_map[i];
    }
    for (uint64_t i = 0; i < kernel_size_in_bytes; i += 0x1000)
    {
        map(((uint64_t)pml4 + hhdm_request.response->offset), (kernel_virt_addr_base + i), (kernel_phys_addr_base + i), 0);
    }
    

    
    // i think this will work
    // flags is
    update_cr3(pml4);
    kflantprint(ft_ctx, "Kernel has been Mapped to New PageMap!", 39, 0xFFFFF, "Virtual Memory Manager", 23, true);
}