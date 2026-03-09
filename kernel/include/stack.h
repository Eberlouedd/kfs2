#ifndef STACK_H
#define STACK_H

#include <stdint.h>

// Prints a simple backtrace using the EBP chain + a raw dump of a few words.
void stack_print_kernel(void);

#endif
