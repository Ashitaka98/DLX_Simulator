#define _CRT_SECURE_NO_WARNINGS
#include"preprocess.h"


extern map<string, INS_TYPE> type_map;

// caseLower2Upper lowercase string to uppercase
static char* caseLower2Upper(char* s) {
	for (int i = 0; i < strlen(s); i++)
		if (s[i] <= 'z' && s[i] >= 'a')
			s[i] = s[i] - 'a' + 'A';
	return s;
}

// initialize memory
void mount_memory_file(char* memory, Memory& mem)
{
	ifstream infile(memory);
	string str;
	while (getline(infile, str)) {
		int i = 0, lab = 0;
		unsigned int addr = 0;
		while (str[i] != ':') {
			if (str[i] >= 'a' && str[i] <= 'z') { str[i] = char('A' - 'a' + str[i]); }
			if (str[i] < 'A')
				addr = ((str[i] - '0') + (addr << 4)) & 0XFFFF;
			else
				addr = ((str[i] - 'A' + 10) + (addr << 4)) & 0XFFFF;
			i++;
		}
		i = i + 3;
		for (int j = 0; j < 2; j++) {
			if (str[i + j] >= 'a' && str[i + j] <= 'z') { str[i + j] = str[i + j] + 'A' - 'a'; }
			if (str[i + j] < 'A')
				lab = (str[i + j] - '0') + (lab << 4);
			else
				lab = (str[i + j] - 'A' + 10) + (lab << 4);
		}
		mem.mem[addr] = lab;
	}
	infile.close();
}



void normalize_code_file(char* input, char* output)
{//
	ifstream fin(input, ios::in);
	ofstream fout(output);
	char buf1[1024] = { 0 };
	char buf2[1024] = { 0 };
	char buf[1024] = { 0 };
	char* A = buf1;
	char* B = buf2;
	char* p;
	int flag = 0;
	fin >> buf1;
	fin >> buf2;
	for (;;) {
		if (strchr(A, ';') != NULL)//×Ö·û´®ÓÐ£»
			if (A[strlen(A) - 1] == ';')
				fout << caseLower2Upper(A) << '\n';
			else {
				p = strtok(A, ";");
				caseLower2Upper(p);
				memset(buf, 0, 1024);
				if (A[0] == ';') {
					fout << ";\n";
					strcpy(buf, A + 1);
				}
				else {
					fout << p << ";\n";
					strcpy(buf, strtok(NULL, ";"));
				}
				memset(A, 0, 1024);
				strcpy(A, buf);
				flag = 1;
			}
		else {
			if (strchr(A, ':') != NULL)//ÎÞ£»ÓÐ£º
				if (A[strlen(A) - 1] == ':')
					fout << caseLower2Upper(A);
				else
					fout << caseLower2Upper(A) << ' ';
			else if (A[0] != '\0') {
				fout << caseLower2Upper(A);
				if (B[0] != ':' && B[0] != ';' && B[0])
					fout << " ";
			}
		}
		if (flag) {
			flag = 0;
			continue;
		}
		else {
			if (B[0] == '\0' && !strchr(A, ';'))
				break;
			p = A; A = B; B = p;
			memset(B, 0, 1024);
			fin >> B;
			flag = 0;
		}
	}
	memcpy(A, "HALT", 4);
	fout << "\n";
	fin.close();
}

// input codefile should be normalized
void profile_code(char* input, map<string, int>& label_map, Code& code)
{
	fstream infile(input);
	if (!infile) return;
	int ins_no = 0;
	string str;
	char* s1, * s2;
	char buffer[128];
	char instruction[128];
	while (getline(infile, str))
	{
		Instruction& ins = code.ins[ins_no];
		// extract label(if exist)
		strcpy(buffer, str.c_str());
		strcpy(instruction, str.c_str());
		if (strchr(buffer, ':')) {
			s1 = strtok(buffer, ":");
			label_map[(string)s1] = ins_no;
			s2 = strtok(NULL, ":");
			strcpy(instruction, s2);
		}
		int opnum = 0;
		char* mark = strtok(instruction, " ");
		while (mark) {
			strcpy(ins.operand[opnum], mark);
			mark = strtok(NULL, " ");
			opnum++;
		}
		ins.op_num = opnum;
		ins.ins_type = type_map.find((string)ins.operand[0])->second;
		if (opnum == 3) {
			bool imme_flag = (ins.operand[2][0] == '-' || (ins.operand[2][0] >= '0' && ins.operand[2][0] <= '9')) ? 1 : 0;
			if (imme_flag)
				ins.imme = atoi(ins.operand[2]);
			ins.rd = atoi(ins.operand[1] + 1);
		}
		else if (opnum == 4) {
			ins.rd = atoi(ins.operand[1] + 1);
			ins.rs1 = atoi(ins.operand[2] + 1);
			bool imme_flag = (ins.operand[3][0] == '-' || (ins.operand[3][0] >= '0' && ins.operand[3][0] <= '9')) ? 1 : 0;
			if (!imme_flag)
				ins.rs2 = atoi(ins.operand[3] + 1);
			else
				ins.imme = atoi(ins.operand[3]);
		}

		ins_no++;
	}
	infile.close();
}


