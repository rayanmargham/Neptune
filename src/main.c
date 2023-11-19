// "Saturan" Kernel
// Do Whatever you want Licence @ 2023

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"
#include "memfunc.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "gdt.h"
#include "idt.h"
#include "pmm.h"
#include "vmm.h"
#include "kheap.h"
#include <lai/core.h>
#include <lai/helpers/sci.h>

// we just tell limine to use the latest limine protocol or something, idk hard to understand 
LIMINE_BASE_REVISION(1)

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, in C, they should
// NOT be made "static".
 

struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt and catch fire function.
static void hcf(void) {
    __asm__ ("cli");
    for (;;) {
        __asm__ ("hlt");
    }
}

void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line)
{
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xFFFFFF);
    flanterm_write(ft_ctx, "[", 1);
    ft_ctx->set_text_fg_rgb(ft_ctx, color);
    flanterm_write(ft_ctx, from_who, length_for_that);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xFFFFFF);
    flanterm_write(ft_ctx, "] ", 3);
    flanterm_write(ft_ctx, msg, count);
    if (next_line)
    {
        flanterm_write(ft_ctx, "\n", 2);
    }
}

struct flanterm_context *ft_ctx;
volatile void _start(void)
{
    __asm__ volatile ("cli");
    // Ensure the bootloader actually understands that base revision
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }
    initgdt();
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }
    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    ft_ctx = flanterm_fb_simple_init(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);
    ft_ctx->set_text_bg_rgb(ft_ctx, 0x1c1c1c);
    ft_ctx->clear(ft_ctx, false);
    kflantprint(ft_ctx, "Terminal is setup!", 19, 0x00FF00, "SUCCESS", 8, true);
    kflantprint(ft_ctx, "GDT Table Loaded!", 18, 0x00FF00, "SUCCESS", 8, true);
    
    kflantprint(ft_ctx, "Setting up IDT...", 18, 0xFFFF00, "Kernel", 7, true);
    init_idt();
    kflantprint(ft_ctx, "IDT Table Loaded!", 18, 0x00FF00, "SUCCESS", 8, true);
    pmm_init();
    kflantprint(ft_ctx, "PMM initialized!", 17, 0x00FF00, "SUCCESS", 8, true);
    vmm_init();
    kheap_init();
    int *x = malloc(sizeof(int));
    *x = 5;
    kflantprint(ft_ctx, to_string(*x), 10, 0xFFFF00, "Kernel", 7, true);
    free(x);
    lai_create_namespace();
    lai_enable_acpi(0);
    hcf();
}
