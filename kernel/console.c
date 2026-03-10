#include "include/console.h"

#define VGA_MEM ((volatile uint16_t*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint8_t  g_color = 0x07;
static uint16_t g_cursor = 0;

static void put_at(uint16_t pos, char c) {
    VGA_MEM[pos] = ((uint16_t)g_color << 8) | (uint8_t)c;
}

void console_clear(void) {
    for (int y = 0; y < VGA_HEIGHT; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            VGA_MEM[y * VGA_WIDTH + x] = ((uint16_t)g_color << 8) | ' ';
    g_cursor = 0;
}

static void newline(void) {
    g_cursor = (g_cursor / VGA_WIDTH + 1) * VGA_WIDTH;
    if (g_cursor >= VGA_WIDTH * VGA_HEIGHT)
        g_cursor = 0;
}

void console_putc(char c) {
    if (c == '\n') {
        newline();
        return;
    }
    put_at(g_cursor, c);
    g_cursor++;
    if (g_cursor >= VGA_WIDTH * VGA_HEIGHT)
        g_cursor = 0;
}

void console_write_n(const char *s, size_t n) {
    if (!s) return;
    for (size_t i = 0; i < n; i++)
        console_putc(s[i]);
}

void console_write(const char *s) {
    if (!s) return;
    while (*s)
        console_putc(*s++);
}

void console_write_hex32(uint32_t v) {
    static const char *hex = "0123456789ABCDEF";
    console_write("0x");
    for (int i = 7; i >= 0; i--) {
        uint8_t nib = (v >> (i * 4)) & 0xF;
        console_putc(hex[nib]);
    }
}
