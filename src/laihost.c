#include <lai/host.h>
#include "kheap.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "memfunc.h"
extern struct flanterm_context *ft_ctx;
void laihost_log(int level, const char *msg)
{
    flanterm_write(ft_ctx, msg, strlen(msg));
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
// void *laihost_scan(const char *sig, size_t index)
// {

// }