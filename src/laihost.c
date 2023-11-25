#include <lai/host.h>
#include "kheap.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "memfunc.h"
#include "acpi.h"
#include "limine.h"
#include "vmm.h"
#include "stdint.h"
extern struct flanterm_context *ft_ctx;
extern volatile struct limine_hhdm_request hhdm_request;
extern uint64_t *pml4; // top level of kernel pagemap
void laihost_log(int level, const char *msg)
{
    flanterm_write(ft_ctx, msg, strlen(msg));
    flanterm_write(ft_ctx, "\n", 2);
}
void *laihost_malloc(size_t size)
{
    return malloc(size);
}

void *laihost_realloc(void *base, size_t newsize, size_t oldsize)
{
    return realloc(base, newsize);
}

void laihost_free(void *base, size_t size)
{
    return free(base);
}
void *laihost_scan(const char *sig, size_t index)
{
    return GetTable(sig, index);
}
void *laihost_map(size_t address, size_t count)
{
    return address + hhdm_request.response->offset;
}