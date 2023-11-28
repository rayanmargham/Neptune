#include "pmm.h"
#include "memfunc.h"
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "vmm.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
struct pmm_list_node
{
    struct pmm_list_node *next;
};

struct pmm_list_node *head;

volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 1
};
volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 1
};
uint64_t end_of_hhdm = 0;
void pmm_init()
{
    struct pmm_list_node *prev_node = NULL;
    uint64_t amount_of_mem = 0;
    for (uint64_t i = 0; i != memmap_request.response->entry_count; i++)
    {
        amount_of_mem += (memmap_request.response->entries[i]->length / 4096);
            switch (memmap_request.response->entries[i]->type)
            {
                case LIMINE_MEMMAP_USABLE:
                    kflantprint(ft_ctx, "Usable Memory Entry, Size: ", 28, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    if (!head)
                    {
                        kflantprint(ft_ctx, "Setting Up Freelist Head", 25, 0xFFA500, "Physical Memory Manager", 24, true);
                        head = memmap_request.response->entries[i]->base + hhdm_request.response->offset;
                    }
                    for (uint64_t j = 0; j < memmap_request.response->entries[i]->length; j += 0x1000)
                    {
                        struct pmm_list_node *epic_gamer;
                        epic_gamer = memmap_request.response->entries[i]->base + j + hhdm_request.response->offset;
                        if (prev_node != NULL)
                        {
                            prev_node->next = epic_gamer;
                        }
                        prev_node = epic_gamer;
                    }
                    prev_node->next = NULL;
                    break;
                case LIMINE_MEMMAP_RESERVED:
                    kflantprint(ft_ctx, "Reversed Memory Entry, Size: ", 30, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
                case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                    kflantprint(ft_ctx, "Reclaimable ACPI Memory Entry, Size: ", 38, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    
                    break;
                case LIMINE_MEMMAP_ACPI_NVS:
                    kflantprint(ft_ctx, "Reversed APCI NVS Memory Entry, Size: ", 39, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
                case LIMINE_MEMMAP_BAD_MEMORY:
                    kflantprint(ft_ctx, "Bad Memory Memory Entry, Size: ", 32, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
                case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
                    kflantprint(ft_ctx, "Reclaimable Bootloader Memory Entry, Size: ", 44, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
                case LIMINE_MEMMAP_KERNEL_AND_MODULES:
                    kflantprint(ft_ctx, "Kernel And Modules Memory Entry, Size: ", 40, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
                case LIMINE_MEMMAP_FRAMEBUFFER:
                    kflantprint(ft_ctx, "FrameBuffer Memory Entry, Size: ", 33, 0xFFA500, "Physical Memory Manager", 24, false);
                    flanterm_write(ft_ctx, to_hstring(memmap_request.response->entries[i]->length), 64);
                    flanterm_write(ft_ctx, "\n", 2);
                    break;
        }
    }
    end_of_hhdm = memmap_request.response->entries[memmap_request.response->entry_count - 1]->base + memmap_request.response->entries[memmap_request.response->entry_count - 1]->length;
    end_of_hhdm = align_up(end_of_hhdm, 4096);
    end_of_hhdm = hhdm_request.response->offset + end_of_hhdm;
    uint64_t count = 0;
    struct pmm_list_node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    kflantprint(ft_ctx, "Free Pages: ", 13, 0xFFA500, "Physical Memory Manager", 24, false);
    flanterm_write(ft_ctx, to_string(count), 64);
    flanterm_write(ft_ctx, "\n", 2);
    kflantprint(ft_ctx, "Total Pages: ", 14, 0xFFA500, "Physical Memory Manager", 24, false);
    flanterm_write(ft_ctx, to_string(amount_of_mem), 14);
    flanterm_write(ft_ctx, "\n", 2);
}

void *pmm_alloc_singlep()
{
    if (!head == NULL)
    {
        struct pmm_list_node *node = head;
        head = head->next;
        return (uint64_t)node - hhdm_request.response->offset;
    }
    else
    {
        kflantprint(ft_ctx, "NO MORE MEMORY *VINE BOOM*", 27, 0xFFA500, "Physical Memory Manager", 24, true);
    }
    
}

void pmm_dealloc_singlep(void *page)
{
    struct pmm_list_node *node = page;
    node->next = head;
    head = page;
    
}

