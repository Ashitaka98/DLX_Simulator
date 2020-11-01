#define _CRT_SECURE_NO_WARNINGS
#define TMP_INSTRUCTION_FILE "tmp_instruction_file"

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<map>
#include"register.h"
#include"instruction.h"
#include"preprocess.h"
using namespace std;

Code code;
Registers regs;
Memory mem;
int PC=0;
map<string,int>label_map;
map<string,INS_TYPE>type_map;
char codefile[100] = { 0 }, memoryfile[100] = { 0 }, outputfile[100] = { 0 };
char tmp_code_file[] = "tmp_code_file";

int main(int argc, char* argv[])
{
	init_registers(&regs, 0);
	init_memory(&mem, 0);
	type_map_init(type_map);

	for (int j = 1; j < argc; j += 2)
	{
		if (memcmp(argv[j], "-i", 2) == 0)
			strcpy(codefile, argv[j + 1]);
		else if (memcmp(argv[j], "-o", 2) == 0)
			strcpy(outputfile, argv[j + 1]);
		else if (memcmp(argv[j], "-m", 2) == 0)
			strcpy(memoryfile, argv[j + 1]);
	}

	mount_memory_file(memoryfile, mem);
	normalize_code_file(codefile, tmp_code_file);
	profile_code(tmp_code_file, label_map, code);

	for (PC; code.ins[PC].ins_type != _HALT; PC++)
	{
		Instruction& ins = code.ins[PC];
		switch (code.ins[PC].ins_type)
		{
		case _HALT:return 0;
		case _ADD: {
			ADD(ins);
			break;
		}
		case _ADDI: {
			ADDI(ins);
			break;
		}
		case _SUB: {
			SUB(ins);
			break;
		}
		case _SUBI: {
			SUBI(ins);
			break;
		}
		case _AND: {
			AND(ins);
			break;
		}
		case _ANDI: {
			ANDI(ins);
			break;
		}

		case _OR: {
			OR(ins);
			break;
		}
		case _ORI: {
			ORI(ins);
			break;
		}

		case _XOR: {
			XOR(ins);
			break;
		}
		case _XORI: {
			XORI(ins);
			break;
		}
		case _SLE: {
			SLE(ins);
			break;
		}
		case _SLEI: {
			SLEI(ins);
			break;
		}
		case _SGT: {
			SGT(ins);
			break;
		}
		case _SGTI: {
			SGTI(ins);
			break;
		}
		case _SEQ: {
			SEQ(ins);
			break;
		}
		case _SEQI: {
			SEQI(ins);
			break;
		}
		case _SGE: {
			SGE(ins);
			break;
		}
		case _SGEI: {
			SGEI(ins);
			break;
		}
		case _SLT: {
			SLT(ins);
			break;
		}
		case _SLTI: {
			SLTI(ins);
			break;
		}
		case _SNE: {
			SNE(ins);
			break;
		}
		case _SNEI: {
			SNEI(ins);
			break;
		}
		case _BEQZ: {
			BEQZ(ins);
			break;
		}
		case _BNEZ: {
			BNEZ(ins);
			break;
		}
		case _SLLI: {
			SLLI(ins);
			break;
		}
		case _SRLI: {
			SRLI(ins);
			break;
		}
		case _LB: {
			LB(ins);
			break;
		}
		case _LW: {
			LW(ins);
			break;
		}
		case _SB: {
			SB(ins);
			break;
		}
		case _SW: {
			SW(ins);
			break;
		}
		case _JR: {
			JR(ins);
			break;
		}
		case _OP: {
			OP(ins);
			break;
		}

		}
	}
	return 0;
}
