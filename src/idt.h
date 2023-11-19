#ifndef _IDT_H_
#define _IDT_H_
#include <stdint.h>
#include <stddef.h>
enum
{
    default_type_attribute_interrupt = 0x8E,
    default_type_attribute_trap = 0x8F,
};

struct idtentry
{
    uint16_t offset1;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attributes;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t reversed;
} __attribute__((packed));
struct idtptr
{
    uint16_t size;
    uintptr_t offset;
} __attribute__((packed));

struct interrupt_frame
{
		uintptr_t ss;
		uintptr_t rbp, ignored1, r15, r14, r13, r12, r11, r10, r9, r8,
				 rdi, rsi, ignored2, rbx, rdx, rcx, rax;
		uintptr_t intNumber, errorCode;
		uintptr_t rip, cs;
		uintptr_t rflags;
		uintptr_t rsp, ds;
};
void RegisterInterruptHandler(unsigned char interrupt, void(*handler)(struct interrupt_frame* frame));
void init_idt();
#endif