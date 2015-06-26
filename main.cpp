#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "dirent.h"
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
//extern "C" void asmMain();
//extern "C" void asmMainD();

//char file[] = "SAMPLE.TXT";

//char file[] = "C:\\Users\\Maciek\\SAMPLE.TXT";//"D:\\Dropbox\\TeX\\MHDD\\instrukcjaMHDD.pdf";


void listujPliki(const char * nazwa_sciezki);
bool czyKatalog(string sciezka);
int main()
{
	setlocale(LC_ALL, "");
	int output;
	string test = "D:\\Dropbox\\Maciej";
	char* file = new char[test.size() + 1];
	strcpy(file, test.c_str());
	
	listujPliki(file);

	//file = "D:\\Dropbox\\TeX\\MHDD\\instrukcjaMHDD.pdf";
	/* Nadawanie atrybutów:
		CX         Attribute specified
		00h        Normal
		01h        Read - only
		02h        Hidden
		04h        System
		20h        Archive
		*/
	/*
	_asm{
		mov eax, 03h
		push eax
		mov  eax, file
		push eax
		call SetFileAttributes
		pop ebx
		pop ebx
	}
	*/

	/* Pobieranie atrybutów z pliku. 
	Zwracana w output wartoœæ jest sum¹ atrybutów w przypadku nadania kilku jednoczeœnie.*//*
	_asm{
		mov eax, file
		push eax
		call GetFileAttributes
		mov output, eax
	}
	cout << output << "\n";*/
	//asmMain();
	//asmMainD();
	system("pause");
	return 0;
}

void listujPliki(const char * nazwa_sciezki){
	struct dirent * plik;
	int output = 0;
	//string file_name = "", pelna_sciezka = "";
	//string test;
	char * file;
	DIR * sciezka;
	struct stat st;

	if ((sciezka = opendir(nazwa_sciezki))) {
		while ((plik = readdir(sciezka))){
			cout << plik->d_name;
			//puts(plik->d_name);
			stat(plik->d_name, &st);
			if (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode)){
				// trzeba z³o¿yæ œcie¿kê do pliku:
				file = new char[strlen(nazwa_sciezki) + strlen(plik->d_name) + 4];
				strcpy(file, nazwa_sciezki);
				if (!czyKatalog(nazwa_sciezki))
					strcat(file, "\\");
				strcat(file, plik->d_name);
				_asm{
					mov eax, file
					push eax
					call GetFileAttributes
					mov output, eax
				}
				cout << "   " << output;
				switch (output){
					case 0x01: // tylko do odczytu
						cout << " ro ";
						break;
					case 0x02: // ukryty
						cout << " h ";
						break;
					case 0x03: // tylko do odczytu i ukryty
						cout << " ro-h ";
						break;
					case 0x04: // systemowy
						cout << " s ";
						break;
					case 0x10: // systemowy
						cout << " dir ";
						break;
					case 0x11: // systemowy
						cout << " dir ro ";
						break;
					case 0x12: // systemowy
						cout << " dir h ";
						break;
					case 0x14: // systemowy
						cout << " dir ro-h ";
						break;
					case 0x20: // archiwalny
						cout << " a ";
						break;
				}
			}
			cout << "\n";
		}
		closedir(sciezka);
	}
	else
		printf("! wywo³uj¹c funkcjê opendir(%s) pojawi³ siê b³¹d otwarcia strumienia dla danej œcie¿ki, mo¿e nie istnieje, lub podano œcie¿kê pust¹\n", nazwa_sciezki);

}
bool czyKatalog(string sciezka){
	if (sciezka.back() == '\\')
		return true;
	return false;
}