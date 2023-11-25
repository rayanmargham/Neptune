#include "memfunc.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
void kpanic(const char *msg)
{
    kflantprint(ft_ctx, msg, strlen(msg), 0xFF0000, "ABORT", 6, true);
}