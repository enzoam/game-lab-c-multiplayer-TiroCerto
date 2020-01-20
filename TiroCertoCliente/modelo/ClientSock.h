#ifndef CLIENTSOCK_H_INCLUDED
#define CLIENTSOCK_H_INCLUDED

#include <iostream>//cout
#include <stdio.h>//perror
#include <stdlib.h> //exit

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct ClientSock {
    int sockfd;
    sockaddr_in cli_addr;
    socklen_t clilen; //sizeof(cli_addr);
};

/*MSG de erro com EXIT*/
void erroSair(const char *msg);

#endif // CLIENTSOCK_H_INCLUDED
