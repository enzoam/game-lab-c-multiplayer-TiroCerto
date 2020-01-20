// TiroCertoServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define SERVER_CONF "serverinfo.conf"

#include "servidor\ClientSock.h"
#include "servidor\ConnServerWin.h"

//Arquivo Ex.: 12345,3
int _tmain(int argc, _TCHAR* argv[]) {
	int porta = 12345;
	int tempoEntreJogada = 3;

	//Leitura de arquivo
	char content[20];
	std::ifstream infile;
	infile.open (SERVER_CONF);
	if (infile.is_open()) 	{
		if (infile.good()){
			infile.getline(content, 256, ',');
			porta = atoi(content);

			infile.getline(content, 256, ',');
			tempoEntreJogada = atoi(content);
		}
		infile.close();
	}
	else {
		printf("\n[SERVER] Nao utilizando arquivo de CONF %s", SERVER_CONF);
	}


	ConnServerWin connServerWin(porta);
	connServerWin.startListening(tempoEntreJogada);
	return 0;
}

