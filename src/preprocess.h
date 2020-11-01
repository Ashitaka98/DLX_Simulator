#pragma once
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<map>
#include"memory.h"
#include"instruction.h"
using namespace std;

void mount_memory_file(char* memory, Memory& mem);

void normalize_code_file(char* input, char* output);

void profile_code(char* normalized_input, map<string, int>& label_map, Code& code);