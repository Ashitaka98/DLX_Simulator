#include "memory.h"

void init_memory(Memory* mem, const int value) {
	memset(mem->mem, value, MAX_MEMORY_SIZE);
}