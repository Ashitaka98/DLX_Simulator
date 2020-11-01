#ifndef __register__h
#define __register__h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registers{
	int reg[32];
}Registers;

void init_registers(Registers * regs, const int value);

#endif