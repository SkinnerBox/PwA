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
	string test = "C:\\Users\\Maciek\\";
	char* file = new char[test.size() + 1];
	strcpy(file, test.c_str());
	
	if( czyKatalog(test) )
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
	}*/
	if (output == (0x04))
		cout << output;
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
			puts(plik->d_name);
			if (stat(plik->d_name, &st) == 0){
				if (st.st_mode & S_IFREG){
					//file_name = plik->d_name;
					file = new char[strlen(nazwa_sciezki) + strlen(plik->d_name)];
					strcpy(file, nazwa_sciezki);
					strcat(file, plik->d_name);

					//test = sciezka + file_name;
					//file = new char[test.size() + 1];
					//strcpy(file, test.c_str());
					_asm{
						mov eax, file
							push eax
							call GetFileAttributes
							mov output, eax
					}
					if (output == (0x04))
						cout << "   u \n";
				}
			}
			
			
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