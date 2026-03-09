#include <stdint.h>

#include "include/console.h"
#include "include/gdt.h"
#include "include/stack.h"

static void level3(uint32_t x) {
    // Add some stack activity
    volatile uint32_t y = x + 0x1234u;
    (void)y;
    stack_print_kernel();
}

static void level2(uint32_t x) { level3(x + 2); }
static void level1(uint32_t x) { level2(x + 1); }

void kernel_main(void) {
    console_clear();
    console_write("KFS_2: GDT & Stack\n");

    // Mandatory: GDT at 0x00000800 and loaded with lgdt
    gdt_init();
    console_write("GDT loaded at ");
    console_write_hex32(GDT_ADDR);
    console_write("\n");

    // Demonstrate the stack + print it in a human-friendly way
    level1(0xDEADBEEFu);

    for (;;) __asm__ __volatile__("hlt");
}
