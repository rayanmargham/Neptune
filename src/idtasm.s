[BITS 64]

global load_idt
load_idt:
    lidt [rdi]
    sti
    ret

%macro pushaq 0
push rax
; rax has rsp.
mov rax, rsp
add rax, 8
push rcx
push rdx
push rbx
push rax ; Push rsp
push rsi
push rdi
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15
push qword [rsp+0x88]
push rbp
%endmacro

; Cleans up after pushaq.

%macro popaq 0
pop rbp
add rsp, 8
pop r15
pop r14
pop r13
pop r12
pop r11
pop r10
pop r9
pop r8
pop rdi
pop rsi
add rsp, 8
pop rbx
pop rdx
pop rcx
pop rax
%endmacro

%macro pushaq_syscall 0
push rax
; rax has rsp.
mov rax, rsp
add rax, 8
push rcx
push rdx
push rbx
push rax ; Push rsp
push rsi
push rdi
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15
push qword [rsp+0x78]
push rbp
%endmacro

%macro popaq_syscall 0
pop rbp
add rsp, 8 ; Skip the pushed rip.
pop r15
pop r14
pop r13
pop r12
pop r11
pop r10
pop r9
pop r8
pop rdi
pop rsi
add rsp, 8 ; Skip the pushed rsp
pop rbx
add rsp, 8 ; Skip rdx
pop rcx
add rsp, 8 ; Skip rax
%endmacro

%macro ISR_NOERRCODE 1
global isr%1
isr%1:
%assign current_isr current_isr + 1
cld
push 0
push %1
jmp isr_common_stub
%endmacro
%macro ISR_ERRCODE 1
global isr%1
isr%1:
%assign current_isr current_isr + 1
cld
push %1
jmp isr_common_stub
%endmacro

%assign current_isr 0

 ISR_NOERRCODE 0
 ISR_NOERRCODE 1
 ISR_NOERRCODE 2
 ISR_NOERRCODE 3
 ISR_NOERRCODE 4
 ISR_NOERRCODE 5
 ISR_NOERRCODE 6
 ISR_NOERRCODE 7
 ISR_ERRCODE   8
 ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE   17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_ERRCODE   21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_ERRCODE   29
ISR_ERRCODE   30
ISR_NOERRCODE 31
%rep 224
ISR_NOERRCODE current_isr
%endrep

extern idt_handlers
isr_common_stub:
    pushaq
    mov rbp, rsp ; setup new stack frame
    mov rax, ss ; mov the data segment and push it to stack
    push rax

    mov rax, [rsp + 0x90] ; get the interrupt number and put it in rax
    mov rax, [idt_handlers + rax * 8]

    test rax, rax ; we check if we got a valid handler
    jz .letsfinishthis ; if we dont we jump and clean up

    mov rdi, rsp ; we put the stack as our parameter so it will be interrupt_frame
    ; since we pushed all our registers already
    call rax ; we go ahead and just call the handler

.letsfinishthis:
    mov rsp, rbp ; make the stack pointer point to the bottom of the stack so the start of the new stack frame
    popaq ; now we pop it off all

    add rsp, 16 ; skip the interrupt number and error code skull emoji

    iretq
