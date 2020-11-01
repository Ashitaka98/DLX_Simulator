#define _CRT_SECURE_NO_WARNINGS
#ifndef __instruction__h
#define __instruction__h

#include <fstream>
#include <iostream>
#include <map>
#include "register.h"
#include "memory.h"
#define MAX_INSTRUCTION_SIZE 100000

using namespace std;

enum INS_TYPE {
    _HALT,
    _ADD,
    _ADDI,
    _SUB,
    _SUBI,
    _AND,
    _ANDI,
    _OR,
    _ORI,
    _XOR,
    _XORI,
    _SLE,
    _SLEI,
    _SGT,
    _SGTI,
    _SEQ,
    _SEQI,
    _SGE,
    _SGEI,
    _SLT,
    _SLTI,
    _SNE,
    _SNEI,
    _BEQZ,
    _BNEZ,
    _SLLI,
    _SRLI,
    _LB,
    _LW,
    _SB,
    _SW,
    _JR,
    _OP
};

extern Registers regs;
extern Memory mem;
extern map<string, int>label_map;
extern int PC;
extern char outputfile[100];

typedef struct Instruction {
    char operand[4][20];
    int rs1, rs2, rd;
    int imme;
    int op_num;
    INS_TYPE ins_type;
}Instruction;

typedef struct Code{
    Instruction ins[MAX_INSTRUCTION_SIZE];
    int count;
}Code;

void type_map_init(map<string, INS_TYPE>& type_map);

inline void  ADD(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] + regs.reg[ins.rs2];
}
inline void  ADDI(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] + ins.imme;
}
inline void  SUB(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] - regs.reg[ins.rs2];
}
inline void  SUBI(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] - ins.imme;
}
inline void  AND(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] & regs.reg[ins.rs2];

}
inline void  ANDI(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] & ins.imme;
}
inline void  OR(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] | regs.reg[ins.rs2];
}
inline void  ORI(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] | ins.imme;
}
inline void  XOR(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] ^ regs.reg[ins.rs2];
}
inline void  XORI(const Instruction& ins)
{
    regs.reg[ins.rd] = regs.reg[ins.rs1] ^ ins.imme;
}
inline void  SLLI(const Instruction& ins)
{
    unsigned int tmpx = (unsigned int)regs.reg[ins.rs1] << ins.imme;
    regs.reg[ins.rd] = tmpx;
}
inline void  SRLI(const Instruction& ins)
{
    unsigned int tmpx = (unsigned int)regs.reg[ins.rs1] >> ins.imme;
    regs.reg[ins.rd] = tmpx;
}
inline void  SGT(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] > regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SGTI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] > ins.imme) ? 1 : 0;
}
inline void  SEQ(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] == regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SEQI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] == ins.imme) ? 1 : 0;
}
inline void  SGE(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] >= regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SGEI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] >= ins.imme) ? 1 : 0;
}
inline void  SLT(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] < regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SLTI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] < ins.imme) ? 1 : 0;
}
inline void  SNE(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] != regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SNEI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] != ins.imme) ? 1 : 0;
}
inline void  SLE(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] <= regs.reg[ins.rs2]) ? 1 : 0;
}
inline void  SLEI(const Instruction& ins)
{
    regs.reg[ins.rd] = (regs.reg[ins.rs1] <= ins.imme) ? 1 : 0;
}
inline void  LW(const Instruction& ins)
{
    int tmpx;
    unsigned int addr = ((unsigned int)regs.reg[ins.rs1] + ins.imme) & 0XFFFF;
    tmpx = mem.mem[addr];
    for (int j = 1; j <= 3; j++) {
        tmpx = (tmpx << 8) | (mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme + j) & 0XFFFF]);
    }
    regs.reg[ins.rd] = tmpx;
}
inline void  SW(const Instruction& ins)
{
    //rs1+imme

    mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme) & 0XFFFF] = regs.reg[ins.rd] >> 24;
    mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme + 1) & 0XFFFF] = (regs.reg[ins.rd] >> 16) & 0xFF;
    mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme + 2) & 0XFFFF] = (regs.reg[ins.rd] >> 8) & 0xFF;
    mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme + 3) & 0XFFFF] = regs.reg[ins.rd] & 0xFF;
}
inline void  LB(const Instruction& ins)
{
    regs.reg[ins.rd] = mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme) & 0XFFFF];
}
inline void  SB(const Instruction& ins)
{
    mem.mem[((unsigned int)regs.reg[ins.rs1] + ins.imme) & 0XFFFF] = regs.reg[ins.rd];
}
inline void  OP(const Instruction& ins) {
    ofstream outfile(outputfile, ios::app);
    if (!outfile) 
        return;
    int rd = atoi(ins.operand[1] + 1);
    if (ins.op_num == 2) {
        outfile << regs.reg[rd] << "\r\n";
        cout << regs.reg[rd] << "\r\n";
    }
    else if (ins.op_num == 3) {

        int imme = atoi(ins.operand[2]);
        int mem_flag1 = regs.reg[rd] + imme;
        unsigned int tmpx;
        tmpx = mem.mem[mem_flag1 & 0XFFFF];
        for (int i = 1; i <= 3; i++)
        {
            tmpx = (tmpx << 8) | (mem.mem[(mem_flag1 + i) & 0XFFFF]);
        }
        int sum = tmpx;
        outfile << sum << "\r\n";
        cout << sum << "\r\n";
    }
}
inline void  BEQZ(const Instruction& ins)
{
    bool if_lab = (ins.operand[2][0] == '-' || (ins.operand[2][0] >= '0' && ins.operand[2][0] <= '9')) ? 0 : 1;
    if (!regs.reg[ins.rd]) {
        if (!if_lab) {
            int imme = atoi(ins.operand[2]);
            PC = PC + imme;
        }
        else
        {
            char lb[20];
            strcpy(lb, ins.operand[2]);
            lb[strlen(lb) - 1] = '\0';
            PC = label_map[lb] - 1;
        }
    }
}
inline void  BNEZ(const Instruction& ins)
{
    bool if_lab = (ins.operand[2][0] == '-' || (ins.operand[2][0] >= '0' && ins.operand[2][0] <= '9')) ? 0 : 1;
    if (regs.reg[ins.rd]) {
        if (!if_lab) {
            int imme = atoi(ins.operand[2]);
            PC = PC + imme;
        }
        else
        {
            char lb[20];
            strcpy(lb, ins.operand[2]);
            lb[strlen(lb) - 1] = '\0';
            PC = label_map[lb] - 1;
        }

    }
}
inline void  JR(const Instruction& ins)
{
    bool if_lab = (ins.operand[1][0] == 'R' && atoi(ins.operand[1]) < 32) ? 0 : 1;
    if (!if_lab) {
        int rd = atoi(ins.operand[1] + 1);
        PC = PC + regs.reg[rd] - 1;
    }
    else
    {
        char lb[20];
        strcpy(lb, ins.operand[1]);
        lb[strlen(lb) - 1] = '\0';
        PC = label_map[lb] - 1;
    }
}

#endif