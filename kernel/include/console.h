#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <stddef.h>

void console_clear(void);
void console_putc(char c);
void console_write(const char *s);
void console_write_n(const char *s, size_t n);
void console_write_hex32(uint32_t v);

#endif
