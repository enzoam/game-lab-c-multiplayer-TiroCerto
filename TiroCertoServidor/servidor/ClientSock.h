#ifndef CLIENTSOCK_H_INCLUDED
#define CLIENTSOCK_H_INCLUDED

#include <iostream>//cout
#include <stdio.h>//perror
#include <stdlib.h> //exit
#include <WinSock2.h>
#include <sys/types.h>
#include "../protocolo/ProtocoloPartida.h"

struct ClientSock {
    SOCKET sckCliente;
    sockaddr_in cli_addr;
    long sockaddr_t;
	char nomePlayer[PLAYER_NOME_MAX];
};

/*MSG de erro com EXIT*/
void erroSair(const char *msg);

#endif // CLIENTSOCK_H_INCLUDED
