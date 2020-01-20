#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <windows.h>

using namespace std;

class UtilWindows {
public:
	UtilWindows(void);
	~UtilWindows(void);

	static string intToStr(int number);
	int random(int min, int max);
	void randomize(void);
	static vector<string> split(string frase, char separador);
	static char* defaultValue(char* valorAtual, char* novoValor);
	static char* appendCharToCharArray(char * arr, char a);
	static void appendCharTam(std::string &str, const size_t vezes, const char paddingChar);
	static wstring LoadStringFromResource(UINT stringID, HINSTANCE inst );
	static void ctow(WCHAR* Dest, const CHAR* Source);
	static void wtoc(CHAR* Dest, const WCHAR* Source);
};
