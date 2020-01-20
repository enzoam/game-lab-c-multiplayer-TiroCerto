#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

#include <malloc.h>

#include "UtilWindows.h"

UtilWindows::UtilWindows(void) {
	srand((unsigned int)time(0));
}

UtilWindows::~UtilWindows(void)
{

}

string UtilWindows::intToStr(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void UtilWindows::randomize(void){
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	rand();
}

int UtilWindows::random(int min, int max) {
	int lowest=min, highest=max;
    int range=(highest-lowest)+1;
    int random_integer;
    //for(int index=min; index<max; index++){
        random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
        //cout << random_integer << endl;
    //}
	return random_integer;
}

vector<string> UtilWindows::split(string frase, char separador) {
	vector<string> aux;
	char *pStr = const_cast<char*>(frase.c_str());
	string pch;
	pch = strtok(pStr, ",");

	while (!pch.empty())
	{
		printf ("%s\n",pch);
		pch = strtok(NULL, ",");
		aux.push_back(pch);
	}

	return aux;
}

char* UtilWindows::defaultValue(char* valorAtual, char* novoValor) {
	if(!valorAtual || (sizeof(valorAtual) == 0 ) || (valorAtual[0] == '\0')){
		valorAtual = novoValor;
	}
	return valorAtual;
}

char* UtilWindows::appendCharToCharArray(char * arr, char a) {
	char * ret = (char*)malloc(sizeof(arr) + 1 + 1);
	strcpy_s(ret, sizeof(arr), arr);
	ret[strlen(ret)] = a;
	ret[sizeof(ret)] = '\0';
  return ret;
}

void UtilWindows::appendCharTam(std::string &str, const size_t vezes, const char paddingChar = '*')
{
    if(vezes > str.size())
    	str.insert(0, vezes - str.size(), paddingChar);
}


wstring UtilWindows::LoadStringFromResource(UINT stringID, HINSTANCE inst ) {
	WCHAR * pBuf = NULL;

	int len = LoadStringW(
		inst,
		stringID,
		reinterpret_cast< LPWSTR >( &pBuf ),
		0 );

	if( len )
		return std::wstring( pBuf, len );
	else
		return std::wstring();
}

void UtilWindows::ctow(WCHAR* Dest, const CHAR* Source) {
    int i = 0;

    while(Source[i] != '\0')
    {
        Dest[i] = (WCHAR)Source[i];
        ++i;
    }
}

void UtilWindows::wtoc(CHAR* Dest, const WCHAR* Source) {
    int i = 0;

    while(Source[i] != '\0')
    {
        Dest[i] = (CHAR)Source[i];
        ++i;
    }
}
