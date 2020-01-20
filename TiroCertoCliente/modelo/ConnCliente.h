#ifndef CONNCLIENTE_H
#define CONNCLIENTE_H

#include <iostream>    //cout
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent



class ConnCliente
{
    public:
        ConnCliente();
        ConnCliente(std::string ip, int port);
        virtual ~ConnCliente();
        bool tryConnect();

        bool send_data(std::string data);
        std::string receive_data(int len);
        void teste();

        /*Getter and Setters*/
        int getPort() { return m_port; }
        void setPort(int port) { m_port = port; }
        sockaddr_in getServer() { return m_server; }
        void setServer(sockaddr_in server) { m_server = server; }
        std::string getIp() { return m_ip; }
        void setIp(std::string ip) { m_ip = ip; }
        bool isServerOn(){return m_serverOn;}
        void setServerOn(bool serverOn){m_serverOn = serverOn;}
    protected:
    private:
        int m_sockfd;
        int m_port;
        struct sockaddr_in m_server;
        std::string m_ip;
        bool m_serverOn;
};

#endif // CONNCLIENTE_H
