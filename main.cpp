#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "dirent.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>

using namespace std;
//extern "C" void asmMain();
//extern "C" void asmMainD();

//char file[] = "SAMPLE.TXT";

//char file[] = "C:\\Users\\Maciek\\SAMPLE.TXT";//"D:\\Dropbox\\TeX\\MHDD\\instrukcjaMHDD.pdf";
string nowy;
string test = "C:\\Users\\mrdaj_000\\Downloads\\PwA-master (3)\\PwA-master";
char* file = new char[test.size() + 1];
char* file2 = new char[test.size() + 1];
char* file3 = new char[test.size() + 1];
char* file4 = new char[test.size() + 1];
char* file5 = new char[test.size() + 1];

char* nowaSciezka(void);
void ukrywanie(string plik);
void szyfrowanie(string plik);
void listujPliki(const char * nazwa_sciezki);
bool czyKatalog(string sciezka);
void enkrypcja(char *buf, unsigned count, unsigned char encryptChar);

int main()
{
	setlocale(LC_ALL, "");
	int output;



	strcpy(file, test.c_str());
	while (file[0] != 'q'){

		listujPliki(file);
		file = nowaSciezka();



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
		//system("pause");
	}
	return 0;
}

char* nowaSciezka(void){
	cout << "Wpisz folder lub sciezke do ktorej chcesz przejsc:" << endl;
	//cin >> dir; // wpisywanie calej sciezki
	//wpisywanie tylko jednego folderu
	getline(cin, nowy);
	if (nowy == ".") {//wracanie do poprzedniego folderu
		string dirtemp = file;
		int length = dirtemp.size() - 2;
		for (int i = length; i > 0; i--){
			if (file[i] == '\\'){
				file[i + 1] = '\0';
				break;
			}
		}
	}
	else if (nowy[1] == ':'){//wpisanie calej sciezki
		nowy = nowy + "\\";
		for (int i = 0; i < 200; i++){
			file[i] = nowy[i];
			if (nowy[i] == '\0'){
				break;
			}
		}
	}
	else if (nowy[0] == 'h' && nowy[1] == 'i' && nowy[2] == 'd' && nowy[3] == 'e'){
		ukrywanie(nowy);
	}
	else if (nowy[0] == 'e' && nowy[1] == 'n' && nowy[2] == 'c' && nowy[3] == 'r' && nowy[4] == 'y' && nowy[5] == 'p' && nowy[6] == 't'){
		szyfrowanie(nowy);
	}
	else{//wchodzenie do nowego folderu
		nowy = "\\" + nowy + "\\";
		char* temp = new char[nowy.size() + 1];
		strcpy(temp, nowy.c_str());
		strcat(file, temp);
	}
	system("cls");
	return file;
}
void szyfrowanie(string plik){
	char* temp3 = new char[plik.size() + 1];
	char* temp4 = new char[plik.size() + 1 - 5];
	strcpy(temp3, plik.c_str());
	for (int i = 0; i < plik.size() + 1 - 8; i++){
		temp4[i] = temp3[i + 8];
	}
	strcpy(file2, file);
	strcat(file2, temp4);
	//strcat(file3, "temp");
	//cout << file2;
	string line;
	ifstream mojplik(file2);
	file3 = file2;

	strcat(file3, "X");
	ofstream tempplik(file3);
	if (mojplik.is_open()){
		while (getline(mojplik, line)){
			char *linia = new char(line.length() + 1);
			strcpy(linia, line.c_str());
			enkrypcja(linia, strlen(linia), 'z');
			//cout << linia << endl;
			tempplik << linia << endl;
		}
		mojplik.clear();
		mojplik.seekg(0, ios::beg);
		mojplik.close();

		char* temp3 = new char[plik.size() + 1];
		char* temp4 = new char[plik.size() + 1 - 5];
		strcpy(temp3, plik.c_str());
		for (int i = 0; i < plik.size() + 1 - 8; i++){
			temp4[i] = temp3[i + 8];
		}
		//cout << file2<<endl;

		strcpy(file2, file);
		strcat(file2, temp4);

		remove(file2);
		tempplik.close();

		char* temp5 = new char[plik.size() + 1];
		char* temp6 = new char[plik.size() + 1 - 5];
		strcpy(temp5, plik.c_str());
		for (int i = 0; i < plik.size() + 1 - 8; i++){
			temp6[i] = temp5[i + 8];
		}
		//cout << file2<<endl;

		strcpy(file4, file);
		strcat(file4, temp6);

		file5 = file4;
		strcat(file5, "X");

		remove(file2);

		cout << endl << file2 << endl << file5 << endl;
		rename(file5, file2);
	}
	else cout << "Nie moge otworzyc pliku";
	////////////////////////////
}

void enkrypcja(char *buf, unsigned count, unsigned char encryptChar)
{
	__asm {
		mov esi, buf
			mov ecx, count
			mov al, encryptChar
		L1 :
		xor[esi], al
			inc esi
			loop L1
	}
}


void ukrywanie(string plik){
	int output = 0;
	char* temp3 = new char[plik.size() + 1];
	char* temp4 = new char[plik.size() + 1 - 5];
	strcpy(temp3, plik.c_str());
	for (int i = 0; i < plik.size() + 1 - 5; i++){
		temp4[i] = temp3[i + 5];
	}
	strcpy(file2, file);
	strcat(file2, temp4);
	cout << file;
	_asm{
		mov eax, file2
			push eax
			call GetFileAttributes
			mov output, eax
	}
	if (output == 0x02 || output == 18){//plik aktualnie ukryty - odkrwanie
		_asm{
			mov eax, 00h
				push eax
				mov  eax, file2
				push eax
				call SetFileAttributes
				pop ebx
				pop ebx
		}
	}
	else{//ukrywanie
		_asm{
			mov eax, 02h
				push eax
				mov  eax, file2
				push eax
				call SetFileAttributes
				pop ebx
				pop ebx
		}
	}
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
		cout << nazwa_sciezki << "\n";
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
					case 0x30: // archiwalny
						cout << " dir a ";
						break;
					case 128: // normalny
						cout << " n ";
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