#include"instruction.h"
void type_map_init(map<string, INS_TYPE>& type_map)
{
	type_map["HALT"] = _HALT;
	type_map["ADD"] = _ADD;
	type_map["ADDI"] = _ADDI;
	type_map["SUB"] = _SUB;
	type_map["SUBI"] = _SUBI;
	type_map["AND"] = _AND;
	type_map["ANDI"] = _ANDI;
	type_map["OR"] = _OR;
	type_map["ORI"] = _ORI;
	type_map["XOR"] = _XOR;
	type_map["XORI"] = _XORI;
	type_map["SLE"] = _SLE;
	type_map["SLEI"] = _SLEI;
	type_map["SGT"] = _SGT;
	type_map["SGTI"] = _SGTI;
	type_map["SEQ"] = _SEQ;
	type_map["SEQI"] = _SEQI;
	type_map["SGE"] = _SGE;
	type_map["SGEI"] = _SGEI;
	type_map["SLT"] = _SLT;
	type_map["SLTI"] = _SLTI;
	type_map["SNE"] = _SNE;
	type_map["SNEI"] = _SNEI;
	type_map["BEQZ"] = _BEQZ;
	type_map["BNEZ"] = _BNEZ;
	type_map["SLLI"] = _SLLI;
	type_map["SRLI"] = _SRLI;
	type_map["LB"] = _LB;
	type_map["LW"] = _LW;
	type_map["SB"] = _SB;
	type_map["SW"] = _SW;
	type_map["JR"] = _JR;
	type_map["OP"] = _OP;
}