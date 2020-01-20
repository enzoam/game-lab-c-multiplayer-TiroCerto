#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "modelo/ConnCliente.h"
#include "modelo/ConnServer.h"


void myerror(const char *msg) {
    std::cout << msg << std::endl;
}

void errorS(const char *msg) {
    myerror(msg);
    exit(1);
}

int main_server(int argc, char *argv[]) {
    //ConnCliente cc;
    //cc.teste();

    ConnServer cs;
    cs.setPort(12345);
    cs.startListening();

    return 0;
}

int main_2(int argc, char *argv[]) {

     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     char bufferCaps[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     /*if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }*/

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){ errorS("ERROR opening socket"); }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = atoi(argv[1]);
     portno = 23457;

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
              errorS("ERROR on binding");
     }

     printf("Servidor INICIADO na porta %i\n",portno);
     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0){ errorS("ERROR on accept"); }

     bzero(buffer,256);
     n = read(newsockfd,buffer,255);

     if (n < 0) errorS("ERROR reading from socket");

     printf("Mensagem recebida: %s\n",buffer);

     for(int i=0; i<sizeof(buffer); i++){
        buffer[i] = toupper(buffer[i]);
     }
     printf("Mensagem a devolver: %s\n",buffer);

     n = write(newsockfd,buffer,256);
     if (n < 0) errorS("ERROR writing to socket");

     close(newsockfd);
     close(sockfd);
     return 0;
}
