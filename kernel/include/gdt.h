#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ADDR 0x00000800u

#define GDT_SEL_KCODE 0x08
#define GDT_SEL_KDATA 0x10
#define GDT_SEL_KSTACK 0x18
#define GDT_SEL_UCODE 0x20
#define GDT_SEL_UDATA 0x28
#define GDT_SEL_USTACK 0x30

void gdt_init(void);

#endif
