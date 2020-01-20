#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>

#include <malloc.h>

#include "Util.h"

Util::Util(void) {
	srand((unsigned int)time(0));
}

Util::~Util(void)
{

}

string Util::intToStr(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void Util::randomize(void){
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	rand();
}

int Util::random(int min, int max) {
	int lowest=min, highest=max;
    int range=(highest-lowest)+1;
    int random_integer;
    //for(int index=min; index<max; index++){
        random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
        //cout << random_integer << endl;
    //}
	return random_integer;
}

vector<string> Util::split(string frase, char separador) {
	vector<string> aux;
	char *pStr = const_cast<char*>(frase.c_str());
	string pch;
	pch.assign(strtok(pStr, ","));

	while (!pch.empty())
	{
		//printf ("%s\n",pch);
		pch = strtok(NULL, ",");
		aux.push_back(pch);
	}

	return aux;
}

char* Util::defaultValue(char* valorAtual, char* novoValor) {
	if(!valorAtual || (sizeof(valorAtual) == 0 ) || (valorAtual[0] == '\0')){
		valorAtual = novoValor;
	}
	return valorAtual;
}

char* Util::appendCharToCharArray(char * arr, char a) {
	char * ret = (char*)malloc(sizeof(arr) + 1 + 1);
	//strcpy_s(ret, sizeof(arr), arr);
	strcpy(ret, arr);
	ret[strlen(ret)] = a;
	ret[sizeof(ret)] = '\0';
  return ret;
}

void Util::appendCharTam(std::string &str, const size_t vezes, const char paddingChar = '*')
{
    if(vezes > str.size())
    	str.insert(0, vezes - str.size(), paddingChar);
}
