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
#include <cstdlib>
using namespace std;
#include "instruction_t.h"
#include "panic.h"

extern instruction_t imem[];
extern int total_icount;

void write_file(string fname)
{
	ofstream fout;
	try
	{
		fout.open(fname.c_str(), ios::binary);
		if(!fout)
			throw 0;
	}
	catch(...)
	{
		panic("无法写入目标文件");
	}
	int i;
	for(i = 1; i <= total_icount; i++)
		fout.write((char*)&imem[i], sizeof(imem[i]));
	fout.close();
}
