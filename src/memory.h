#ifndef __memory__h
#define __memory__h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MEMORY_SIZE 70000

typedef struct Memory{
	int mem[MAX_MEMORY_SIZE];
}Memory;

void init_memory(Memory * m, const int value);

#endif