#include "register.h"

void init_registers(Registers * regs, const int value){
	memset(regs->reg, value, 32);
}