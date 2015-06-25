#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

//extern "C" void asmMain();
//extern "C" void asmMainD();

//char file[] = "SAMPLE.TXT";
string file;
int output;

int main()
{

	file = "SAMPLE.TXT";
	/* Nadawanie atrybut�w:
		CX         Attribute specified
		00h        Normal
		01h        Read - only
		02h        Hidden
		04h        System
		20h        Archive
		*/
	_asm{
		mov eax, 02h
		push eax
		mov  eax, offset file
		push eax
		call SetFileAttributes
		pop ebx
		pop ebx
	}

	/* Pobieranie atrybut�w z pliku. 
	Zwracana w output warto�� jest sum� atrybut�w w przypadku nadania kilku jednocze�nie.*/
	_asm{
		mov eax, offset file
		push eax
		call GetFileAttributes
		mov output, eax
	}
	if (output == (0x02))
		cout << output;
	//asmMain();
	//asmMainD();
	system("pause");
	return 0;
}