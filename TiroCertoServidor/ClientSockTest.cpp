// ClientSockTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <WinSock2.h>
#include "protocolo\ProtocoloPartida.h"


int _tmain(int argc, _TCHAR* argv[])
{

	//ConnServidor
				AutenticacaoHeader autenticacaoHeader;
				AutenticacaoRequest autenticacaoRequest;
				autenticacaoHeader.status = AUTH_STATUS_CONNECT;
				autenticacaoRequest.cabecalho = autenticacaoHeader;
				autenticacaoRequest.login = "MyLogin";
				autenticacaoRequest.senha = "MySenha";
				//TODO depois de recebido o IP e PORTA do server
				WSADATA wsaData;
				WSAStartup(MAKEWORD(2,2), &wsaData);
				SOCKET principalSocket;
				principalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				if (principalSocket == INVALID_SOCKET) { closesocket(principalSocket); }
					sockaddr_in enderecoServidor;
					enderecoServidor.sin_family = AF_INET;
					enderecoServidor.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr(INADDR_ANY);//0.0.0.0 
					enderecoServidor.sin_port = htons(12345);
				//bind(principalSocket, (SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor));
				connect( principalSocket, (SOCKADDR*) &enderecoServidor, sizeof(enderecoServidor) );
					sockaddr_in remetente;
					int rementeSize = sizeof(remetente);
					//sendto(principalSocket, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), NULL,(SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor));
					int b = send(principalSocket, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0);
					printf("Bytes sent %d", b);
					closesocket(principalSocket);
					WSACleanup();

					//getchar();
	return 0;
}

