// main.cpp

// Older versions of the Visual C++ compiler required you
// insert a statement at the beginning of main() that
// declared and assigned a floating-point variable in order
// to load the floating-point library.

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
using namespace std;

extern "C" void asmMain();
extern "C" void asmMainD();

//char file[] = "SAMPLE.TXT";
string file = "D:\SAMPLE.TXT";

int main()
{
	_asm{
		mov eax, 02h
		push eax
		mov  eax, offset file
		push eax
		call SetFileAttributes
		pop ebx
		pop ebx
	}
	//asmMain();
	//asmMainD();
	system("pause");
	return 0;
}