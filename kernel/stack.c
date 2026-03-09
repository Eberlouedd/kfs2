#include "include/stack.h"
#include "include/console.h"

// Provided by boot/boot.asm
extern unsigned char stack_bottom;
extern unsigned char stack_top;

static uint32_t read_ebp(void) {
    uint32_t ebp;
    __asm__ __volatile__("mov %%ebp, %0" : "=r"(ebp));
    return ebp;
}

static uint32_t read_esp(void) {
    uint32_t esp;
    __asm__ __volatile__("mov %%esp, %0" : "=r"(esp));
    return esp;
}

static int in_kernel_stack(uint32_t p) {
    uint32_t lo = (uint32_t)&stack_bottom;
    uint32_t hi = (uint32_t)&stack_top;
    return (p >= lo) && (p < hi);
}

void stack_print_kernel(void) {
    uint32_t esp = read_esp();
    uint32_t ebp = read_ebp();

    console_write("\n[KERNEL STACK]\n");
    console_write("ESP="); console_write_hex32(esp);
    console_write(" EBP="); console_write_hex32(ebp);
    console_write("\n");

    console_write("Backtrace:\n");

    for (int depth = 0; depth < 5; depth++) {
        if (!in_kernel_stack(ebp) || !in_kernel_stack(ebp + 8)) {
            console_write("stop\n");
            break;
        }

        uint32_t *frame = (uint32_t *)ebp;
        uint32_t prev_ebp = frame[0];
        uint32_t ret_addr = frame[1];
        uint32_t arg0     = frame[2];

        console_write("#");
        console_putc('0' + depth);
        console_write(" EBP=");
        console_write_hex32(ebp);
        console_write(" RET=");
        console_write_hex32(ret_addr);
        console_write(" ARG0=");
        console_write_hex32(arg0);
        console_write("\n");

        if (prev_ebp == 0 || prev_ebp == ebp || !in_kernel_stack(prev_ebp)) {
            console_write("stop\n");
            break;
        }

        ebp = prev_ebp;
    }
}