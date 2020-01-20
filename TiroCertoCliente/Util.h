#pragma once

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Util {
public:
	Util(void);
	~Util(void);

	static string intToStr(int number);
	int random(int min, int max);
	void randomize(void);
	static vector<string> split(string frase, char separador);
	static char* defaultValue(char* valorAtual, char* novoValor);
	static char* appendCharToCharArray(char * arr, char a);
	static void appendCharTam(std::string &str, const size_t vezes, const char paddingChar);
};
