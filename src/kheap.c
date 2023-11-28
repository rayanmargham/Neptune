#include "kheap.h"
#include "pmm.h"
#include "memfunc.h"
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "vmm.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
extern volatile struct limine_hhdm_request hhdm_request;


struct slab_entry
{
    struct slab_entry *next;
};

struct slab
{
    size_t size;
    struct slab_entry *head;
};

struct slab_header
{
    struct slab *slab;
};

static struct slab epic_gamer_slabs[8];

void slab_init(size_t size, struct slab *ptr)
{
    void *page = pmm_alloc_singlep();

    ptr->size = size;
    
    size_t how_much_can_fit_yo_mama_so_fat = 4096 / size;

    struct slab_header *epic = (struct slab_header*)((uint64_t)page + hhdm_request.response->offset);

    epic->slab = ptr;
    
    for (int i = 1; i < how_much_can_fit_yo_mama_so_fat; i += 1)
    {
        struct slab_entry *epic_gamer = (struct slab_entry*)(((uint64_t)page + hhdm_request.response->offset) + (i * size));
        epic_gamer->next = ptr->head;
        ptr->head = epic_gamer;
    }
}

void *malloc(size_t size)
{
    struct slab *found_your_balls = NULL;
    for (int i = 0; i < 8; i++)
    {
        if (epic_gamer_slabs[i].size <= size)
        {
            continue;
        }
        found_your_balls = &epic_gamer_slabs[i];
        break;
    }
    if (found_your_balls == NULL)
    {
        uint64_t aligned = align_up(size, 4096);
        return vmm_alloc(aligned / 4096);
    }
    if (!found_your_balls->head)
    {
        slab_init(found_your_balls->size, found_your_balls);
        if (!found_your_balls->head)
        {
            return NULL;
        }
        
    }
    struct slab_entry *we_already_have_it = found_your_balls->head;
    found_your_balls->head = we_already_have_it->next;
    memset(we_already_have_it, 0, found_your_balls->size);
    return we_already_have_it;
}

void *realloc(void *old_guy, size_t new_size)
{
    if (!old_guy)
    {
        return malloc(new_size);
    }
    if ((uint64_t)old_guy & ~0xFFFULL == (uint64_t)old_guy)
    {
        flanterm_write(ft_ctx, "THIS GUY IS A PAGE, NOT A SLAB GRRR", 36);
        flanterm_write(ft_ctx, "\n", 2);
    }
    struct slab_header *page = (((uint64_t)old_guy) & ~0xFFFULL);
    struct slab *slab = page->slab;
    if (new_size <= slab->size)
    {
        return old_guy;
    }
    void *epic_new_guy = malloc(new_size);
    if (!epic_new_guy)
    {
        return NULL;
    }
    else
    {
        memcpy(epic_new_guy, old_guy, slab->size);
        free(old_guy);
        return epic_new_guy;
    }
}
void free(void *uhoh)
{
    if ((uint64_t)uhoh & ~0xFFFULL == (uint64_t)uhoh)
    {
        vmm_free(uhoh);
        return;
    }
    struct slab_header *page = (((uint64_t)uhoh) & ~0xFFFULL);
    struct slab *slab = page->slab;
    struct slab_entry *inital = slab->head;
    struct slab_entry *ohoh = uhoh;
    ohoh->next = inital;
    slab->head = ohoh;
}

void kheap_init()
{
    slab_init(8, &epic_gamer_slabs[0]);
    slab_init(16, &epic_gamer_slabs[1]);
    slab_init(32, &epic_gamer_slabs[2]);
    slab_init(64, &epic_gamer_slabs[3]);
    slab_init(128, &epic_gamer_slabs[4]);
    slab_init(256, &epic_gamer_slabs[5]);
    slab_init(512, &epic_gamer_slabs[6]);
    slab_init(1024, &epic_gamer_slabs[7]);
}