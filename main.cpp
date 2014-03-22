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
#include <vector>
using namespace std;
#include "instruction_t.h"
//read_file.cpp
void read_file(string fname);
//write_file.cpp
void write_file(string fname);

instruction_t imem[1024 * 1024];
int total_icount;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		cout << "Mosseta-Compiler  Copyright (C) 2014 DLaboratory" << endl;
		cout << "Version 0.0.1-rev2" << endl;
		cout << "This program comes with ABSOLUTELY NO WARRANTY" << endl;
		cout << "This is free software, and you are welcome to redistribute it under certain conditions." << endl;
		cout << "Usage : " << argv[0] << " src.asm dest.bin" << endl;
		return 0;
	}
	else if(argc == 3)
	{
		read_file((string)argv[1]);
		write_file((string)argv[2]);
	}
    return 0;
}
