#include <WinSock2.h>
#include <stdlib.h>
#include <iostream>
#define PACKET_SIZE 1024

int main_server(){
	int r = 0;
	WSADATA wsaData;
	r = WSAStartup(MAKEWORD(2,2), &wsaData);

	if(r != 0){
		std::cout << "Ocorreu erro ao registra a rede: "
				  << WSAGetLastError();
	}

	//Criando socket
	SOCKET principalSocket;
	principalSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (principalSocket == INVALID_SOCKET) {
		std::cout << "Ocorreu um erro ao criar o socket: " << WSAGetLastError();
		closesocket(principalSocket);
	}

	//Endereco para bind
	sockaddr_in enderecoServidor;
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_addr.s_addr = INADDR_ANY;
	enderecoServidor.sin_port = htons(23456);

	r = bind(principalSocket, (SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor));
	if (r != 0) {
			std::cout << "Socket nao aberto: " << WSAGetLastError();
			return 1;
	}

	char buffer[PACKET_SIZE];
	ZeroMemory(buffer, PACKET_SIZE);

	int rev;
	sockaddr_in remetente;
	int rementeSize = sizeof(remetente);
	do{
		rev = recvfrom(principalSocket,
			buffer,
			PACKET_SIZE, NULL, 
			(SOCKADDR*)&remetente,
			&rementeSize);
		std::cout << "\nConteudo recebido: " << buffer << std::endl;
		for (int i = 0; i < sizeof(buffer); i++){
			buffer[i]=toupper(buffer[i]);
		}
		
		//Remetente
		rev = sendto(principalSocket,
			buffer,
			PACKET_SIZE, NULL, 
			(SOCKADDR*)&remetente,
			sizeof(remetente));

		std::cout << "\nConteudo enviado: " << buffer << std::endl;



	}while (true);


	WSACleanup();

	return 1;
	r = listen(principalSocket, SOMAXCONN);
	if (r != 0) {
		std::cout << "Socket sem escuta: " << WSAGetLastError();
		return 1;
	}else{
		std::cout << "Servidor na escuta";
	}


	//Socket da conversa
	SOCKET clienteComCliente;
	sockaddr_in enderecoCliente;
	int tamEnderecoCliente = sizeof(enderecoCliente);
	clienteComCliente = accept(principalSocket, (SOCKADDR*)&enderecoCliente, &tamEnderecoCliente );
	
	char *bemVindo = "Bem Vindo! - Para sair = 0";
	send(clienteComCliente, bemVindo, strlen(bemVindo), 0);

	int sair=0;
	while(sair==0){

		char buffer[1];
		if(recv(clienteComCliente, buffer, 1, 0)) { 
			buffer[0] = toupper(buffer[0]);
			printf("%c\n", buffer[0]);

			send(clienteComCliente, buffer, sizeof(buffer), 0);
			if(buffer[0] == '0'){
				sair =1;
			}
		}
	}

	closesocket(clienteComCliente);
	closesocket(principalSocket);
	WSACleanup();



	return 0;
}
