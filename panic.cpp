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
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

string get_timer()
{
	char buffer[32] = {};
	sprintf(buffer, "[%f] ", (clock() * 1.0 / CLOCKS_PER_SEC));
	return (string)buffer;
}

void panic(string msg)
{
	cout << "(!!) " << get_timer() << "Program Panic!" << endl;
	cout << "(!!) " << get_timer() << "Info:" << msg << endl;
	exit(-1);
}
