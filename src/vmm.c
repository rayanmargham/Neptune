#include "vmm.h"
#include "pmm.h"
#include "memfunc.h"
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "kheap.h"
#define _SATURN_PRESENT_BITMASK 0x1
#define _SATURN_READWRITE_BITMASK 0x2
uint64_t *pml4;
extern uint64_t end_of_hhdm;
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
    uint64_t base; // virtual addr
    uint64_t pages;
    uint64_t flags;
    struct vmm_memory_region *next;
};
struct vmm_memory_region *vmm_head = NULL;
void *vmm_alloc(int pages)
{
    if (vmm_head == NULL)
    {
        vmm_head = malloc(sizeof(struct vmm_memory_region));
        vmm_head->base = end_of_hhdm;
        vmm_head->pages = pages;

        for (int i = 0; i != pages; i++)
        {
            void *page = pmm_alloc_singlep();
            map(((uint64_t)pml4 + hhdm_request.response->offset), (vmm_head->base + (i * 4096)), page, _SATURN_PRESENT_BITMASK | _SATURN_READWRITE_BITMASK);
        }
        return vmm_head->base;
    }
    else
    {
        struct vmm_memory_region *bruh = malloc(sizeof(struct vmm_memory_region));
        uint64_t length_in_bytes = 0;
        length_in_bytes = (vmm_head->base + (vmm_head->pages * 4096));
        bruh->base = length_in_bytes;
        bruh->pages = pages;
        for (int i = 0; i != pages; i++)
        {
            void *page = pmm_alloc_singlep();
            map(((uint64_t)pml4 + hhdm_request.response->offset), (bruh->base + (i * 4096)), page, _SATURN_PRESENT_BITMASK | _SATURN_READWRITE_BITMASK);
        }
        struct vmm_memory_region *prev = vmm_head;
        vmm_head = bruh;
        vmm_head->next = prev;
        return bruh->base;
    }
}
void vmm_free(void *base)
{
    struct vmm_memory_region *prev;
    struct vmm_memory_region *tmp_head = vmm_head;
    if (tmp_head == NULL)
    {
        kflantprint(ft_ctx, "There are no regions bro", 25, 0xFFFFF, "Virtual Memory Manager", 23, true);
        return; // THERE ARE NO REGIONS GRRRR
    }
    while (true)
    {
        bool found = false;
        for (int i = tmp_head->base; i < tmp_head->pages; i++)
        {

            uint64_t our_virt_addr = (tmp_head->base + (i * 4096));
            if (base == our_virt_addr)
            {
                found = true;
                break;
            }
        }
        if (found == true)
        {
            break;
        }
        if (!tmp_head == NULL)
        {
            prev = tmp_head;
            tmp_head = tmp_head->next;
            if (tmp_head == NULL)
            {
                kflantprint(ft_ctx, "Region doesn't exist!", 22, 0xFFFFF, "Virtual Memory Manager", 23, true);
                return; // sorry buckroo but the region doesnt exist
            }
        }
    }
    prev->next = tmp_head->next; //unlink our region
    for (int i = tmp_head->base; i < tmp_head->pages; i++)
    {

        uint64_t our_virt_addr = (tmp_head->base + (i * 4096));
        unmap(pml4, our_virt_addr);
    }
}
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


uint64_t *get_next_lvl(uint64_t *table, uint64_t index, uint64_t flags)
{
    if ((table[index] & _SATURN_PRESENT_BITMASK) == 0)
    {
        // table indexxed does not exist, allocate that shit
        uint64_t *new_table = pmm_alloc_singlep(); // pmm returns phys addr

        memset((uint64_t)new_table + hhdm_request.response->offset, 0, 4096);

        uint64_t entry = 0;
        entry = entry | (uint64_t)new_table;

        entry = entry | flags;
        
        table[index] = entry;
        return (table[index] & 0x000FFFFFFFFFF000);
    }
    else
    {
        return (table[index] & 0x000FFFFFFFFFF000);
    }
}
uint64_t *get_next_lvl_unmap(uint64_t *table, uint64_t index)
{
    if ((table[index] & _SATURN_PRESENT_BITMASK) != 0 && table != NULL)
    {
        return (table[index] & 0x000FFFFFFFFFF000);
    }
    else
    {
        return NULL;
    }
}
void map(uint64_t *pml4, uintptr_t virt_addr, uintptr_t phys_addr, uint64_t flags)
{
    uint64_t lvl4_index = (virt_addr >> 39) & 0x1FF; // SHOULD BE ROOT PAGE TABLE (PML4)
    uint64_t lvl3_index = (virt_addr >> 30) & 0x1FF; // SHOULD BE PAGE POINTER DESCRIPTOR
    uint64_t lvl2_index = (virt_addr >> 21) & 0x1FF; // SHOULD BE PAGE DESCRIPTOR
    uint64_t lvl1_index = (virt_addr >> 12) & 0x1FF; // SHOULD BE PAGE TABLE
    
    uint64_t *cur_table;
    cur_table = get_next_lvl(pml4, lvl4_index, flags);
    cur_table = get_next_lvl((uint64_t)cur_table + hhdm_request.response->offset, lvl3_index, flags);
    cur_table = get_next_lvl((uint64_t)cur_table + hhdm_request.response->offset, lvl2_index, flags);
    // we've gotten the page table, now we give the phys address and whatever tf
    uint64_t entry = 0;

    entry = entry | (uint64_t) phys_addr;
    entry = entry | flags;
    // the funny!
    ((uint64_t*)((uint64_t)cur_table + hhdm_request.response->offset))[lvl1_index] = entry;
}
void unmap(uint64_t *pml4, uintptr_t virt_addr)
{
    uint64_t lvl4_index = (virt_addr >> 39) & 0x1FF; // SHOULD BE ROOT PAGE TABLE (PML4)
    uint64_t lvl3_index = (virt_addr >> 30) & 0x1FF; // SHOULD BE PAGE POINTER DESCRIPTOR
    uint64_t lvl2_index = (virt_addr >> 21) & 0x1FF; // SHOULD BE PAGE DESCRIPTOR
    uint64_t lvl1_index = (virt_addr >> 12) & 0x1FF; // SHOULD BE PAGE TABLE
    
    uint64_t *cur_table;
    cur_table = get_next_lvl_unmap(pml4, lvl4_index);
    cur_table = get_next_lvl_unmap((uint64_t)cur_table + hhdm_request.response->offset, lvl3_index);
    cur_table = get_next_lvl_unmap((uint64_t)cur_table + hhdm_request.response->offset, lvl2_index);
    if (cur_table != NULL)
    {
        ((uint64_t*)((uint64_t)cur_table + hhdm_request.response->offset))[lvl1_index] = 0;
        // invalidate the page
        __asm__ volatile ("invlpg (%0)" :: "b" (virt_addr) : "memory");
    }
}

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
        map(((uint64_t)pml4 + hhdm_request.response->offset), (kernel_virt_addr_base + i), (kernel_phys_addr_base + i), _SATURN_PRESENT_BITMASK | _SATURN_READWRITE_BITMASK);
    }

    
    // i think this will work
    // flags is
    update_cr3(pml4);
    kflantprint(ft_ctx, "Kernel has been Mapped to New PageMap!", 39, 0xFFFFF, "Virtual Memory Manager", 23, true);
}