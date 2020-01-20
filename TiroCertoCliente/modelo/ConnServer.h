#ifndef CONNSERVER_H
#define CONNSERVER_H

#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "ClientSock.h"

class ConnServer
{
    public:
        ConnServer();
        ConnServer(int port);
        virtual ~ConnServer();

        void startListening();

        /*Get and Sets*/
        int getSockfd() { return m_sockfd; }
        void setSockfd(int sockfd) { m_sockfd = sockfd; }
        int getPort() { return m_port; }
        void setPort(int port) { m_port = port; }
        std::vector<ClientSock> getVecClientSock() { return m_vecClientSock; }
        void setVecClientSock(std::vector<ClientSock> clientSock) { m_vecClientSock = clientSock; }
    protected:
    private:
        int m_sockfd;
        int m_port;
        std::vector<ClientSock> m_vecClientSock;
};

#endif // CONNSERVER_H
