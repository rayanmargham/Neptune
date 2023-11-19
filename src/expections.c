#include "expections.h"
#include "idt.h"
#include "memfunc.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
void Page_Fault(struct interrupt_frame* frame)
{
    kflantprint(ft_ctx, "Yo MAMA so fat she paged faulted, Error Code: 0x", 49, 0xFF0000, "PAGE FAULT!", 12, false);
    // flanterm_write(ft_ctx, to_hstring(frame->errorCode), 1);
    // 
    uint8_t real;
    flanterm_write(ft_ctx, to_hstring(frame->errorCode), 2);
    flanterm_write(ft_ctx, "\n", 2);
    flanterm_write(ft_ctx, "CR2: ", 6);
    uint64_t cr2;
    __asm__ volatile ("mov %%cr2, %0" : "=r"(cr2) :: "memory");
    flanterm_write(ft_ctx, to_hstring(cr2), 64);
    flanterm_write(ft_ctx, "\n", 2);

    __asm__ ("cli");
    for (;;) {
        __asm__ ("hlt");
    }
}
void g_p_fault(struct interrupt_frame *frame)
{
    kflantprint(ft_ctx, "Yo MAMA so fat she GENERAL PROTECTED HERSELF!, Error Code: 0x", 62, 0xFF0000, "GP FAULT!", 10, false);
    flanterm_write(ft_ctx, to_hstring(frame->errorCode), 2);
    flanterm_write(ft_ctx, "\n", 2);
    __asm__ ("cli");
    for (;;) {
        __asm__ ("hlt");
    }
}
void register_expections_isrs()
{
    RegisterInterruptHandler(14, Page_Fault);
    RegisterInterruptHandler(13, g_p_fault);
}