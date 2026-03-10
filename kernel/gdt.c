#include "include/gdt.h"

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define GDT_COUNT 7

static struct gdt_entry *g_gdt = (struct gdt_entry*)GDT_ADDR;
static struct gdt_ptr    g_gdtp;

extern void gdt_flush(uint32_t gdt_ptr_addr);

static void gdt_set_entry(
    int i,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t gran
) {
    g_gdt[i].base_low    = (uint16_t)(base & 0xFFFF);
    g_gdt[i].base_mid    = (uint8_t)((base >> 16) & 0xFF);
    g_gdt[i].base_high   = (uint8_t)((base >> 24) & 0xFF);

    g_gdt[i].limit_low   = (uint16_t)(limit & 0xFFFF);
    g_gdt[i].granularity = (uint8_t)((limit >> 16) & 0x0F);
    g_gdt[i].granularity |= (uint8_t)(gran & 0xF0);
    g_gdt[i].access      = access;
}

void gdt_init(void) {
    g_gdtp.limit = (uint16_t)(sizeof(struct gdt_entry) * GDT_COUNT - 1);
    g_gdtp.base  = (uint32_t)g_gdt;

    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_entry(5, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    gdt_set_entry(6, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((uint32_t)&g_gdtp);
}
