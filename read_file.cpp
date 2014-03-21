/*
DLaboratory Mosseta Machine Binary Code Compiler
Copyright (C) 2014 DLaboratory

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#include "instruction_t.h"
#include "panic.h"

extern instruction_t imem[];
extern int total_icount;
map<string, int> label;

string parse_inst(const string &src)
{
	string buffer;
	int i, l = src.length();
	for(i = 0; i < l; i++)
		if(src[i] > 32)
			buffer = buffer + src[i];
		else if(buffer != "")
			return buffer;
	return buffer;
}

void parse_line(vector<string> &para, const string &src)
{
	para.clear();
	if(parse_inst(src) == "")
		return;
	string buffer, a = src;
	int i, l = a.length();
	for(i = 0; i < l; i++)
		if(a[i] == ',')
			a[i] = ' ';
	for(i = 0; i < l; i++)
	{
		if(a[i] == '\"')
		{
			para.push_back(buffer + a.substr(i, l-i+1));
			return;
		}
		else if(i < l-1 && a[i] == ' ' && a[i+1] > 32)
		{
			para.push_back(buffer);
			buffer.clear();
		}
		else if(a[i] > 32)
		{
			buffer = buffer + a[i];
		}
	}
	if(buffer != "")
		para.push_back(buffer);
}

opCode parse_opcode(const string &src)
{
	if(src == "halt")
		return HALT;
	else if(src == "mov")
		return MOV;
	else if(src == "ld")
		return LD;
	else if(src == "st")
		return ST;
	else if(src == "push")
		return PUSH;
	else if(src == "pop")
		return POP;
	else if(src == "add")
		return ADD;
	else if(src == "sub")
		return SUB;
	else if(src == "mul")
		return MUL;
	else if(src == "div")
		return DIV;
	else if(src == "mod")
		return MOD;
	else if(src == "or")
		return OR;
	else if(src == "and")
		return AND;
	else if(src == "xor")
		return XOR;
	else if(src == "cmp")
		return CMP;
	else if(src == "nop")
		return NOP;
	else if(src == "call")
		return CALL;
	else if(src == "ret")
		return RET;
	else if(src == "jmp")
		return JMP;
	else if(src == "jlo")
		return JLO;
	else if(src == "jeq")
		return JEQ;
	else if(src == "jhi")
		return JHI;
	else if(src == "jle")
		return JLE;
	else if(src == "jeh")
		return JEH;
	else if(src == "jne")
		return JNE;
	else if(src == "read")
		return READ;
	else if(src == "write")
		return WRITE;
	return HALT;
}

int parse_int(const string src)
{
	int ans = 0, i, l = src.length();
	for(i = 0; i < l; i++)
		ans = ans * 10 + src[i] - '0';
	return ans;
}

int parse_dmem(const string src)
{
	int ans = 0, i, l = src.length();
	for(i = 0; i < l; i++)
		if(src[i] != ':')
			ans = ans * 10 + src[i] - '0';
		else
			break;
	ans = ans * 1024;
	for(++i; i < l; i++)
		ans = ans * 10 + src[i] - '0';
	return ans;
}

float parse_float(const string src)
{
	float ans = 0.0f;
	int i, l = src.length(), dot = -1;
	for(i = 0; i < l; i++)
		if(src[i] == '.')
			dot = i;
		else if(src[i] >= '0' && src[i] <= '9')
		{
			if(dot == -1)
				ans = ans * 10 + src[i] - '0';
			else
				ans += pow(10, dot-i) * (src[i] - '0');
		}
	return ans;
}

void read_file(string fname)
{
	ifstream fin;
	try
	{
		fin.open(fname.c_str());
		if(!fin)
			throw 0;
	}
	catch(...)
	{
		panic("无法打开源程序");
	}
	int i, sz, icount = 0, lcount = 0, itmp;
	float ftmp;
	string src, inst;
	vector<string> para;
	while(fin)
	{
		getline(fin, src);
		++lcount;
		if(src == "")
			continue;
		inst = parse_inst(src);
		if(inst == "" || inst[0] == ';')
			continue;
		++icount;
		if(inst[0] == ':')
		{
			label[inst] = icount;
			imem[icount].inst = NOP;
		}
		else
		{
			imem[icount].inst = parse_opcode(inst.substr(1, inst.length()-1)); //ipush
			parse_line(para, src);
			sz = para.size();
			for(i = 1; i < sz; i++)
			{
				if(para[i][0] == 'r')
				{
					imem[icount].constant[i-1] = -1;
					imem[icount].iarg[i-1] = parse_int(para[i].substr(1, para[i].length()-1));
				}
				else if(para[i][0] == 'f')
				{
					imem[icount].constant[i-1] = -1;
					imem[icount].iarg[i-1] = 1024 + parse_int(para[i].substr(1, para[i].length()-1));
				}
				else if(para[i][0] == '[')
				{
					imem[icount].constant[i-1] = 0;
					imem[icount].iarg[i-1] = parse_dmem(para[i].substr(1, para[i].length()-2));
				}
				else if(para[i][0] >= '0' && para[i][0] <= '9')
				{
					imem[icount].constant[i-1] = 1;
					itmp = parse_int(para[i]);
					imem[icount].iarg[i-1] = *reinterpret_cast<unsigned int*>(&itmp);
				}
				else if(para[i][para[i].length()-1] == 'f') //0.0f
				{
					imem[icount].constant[i-1] = 1;
					ftmp = parse_float(para[i].substr(0, para[i].length()-1));
					imem[icount].iarg[i-1] = *reinterpret_cast<unsigned int*>(&ftmp);
				}
				else if(para[i][0] == ':')
				{
					imem[icount].constant[i-1] = 1;
					imem[icount].iarg[i-1] = label[para[i]];
				}
				else
				{
					cout << "编译错误 at line " << lcount << endl;
					fin.close();
					panic("编译错误");
				}
			}
		}
	}
	total_icount = icount;
	fin.close();
}
