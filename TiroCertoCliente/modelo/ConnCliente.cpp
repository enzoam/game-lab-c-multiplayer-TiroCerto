#include "ConnCliente.h"

ConnCliente::ConnCliente()
{
    //ctor
}

ConnCliente::ConnCliente(std::string ip, int port) {
    this->m_sockfd = -1;
    this->m_ip = ip;
    this->m_port = port;
}


ConnCliente::~ConnCliente() {
    close(this->m_sockfd);
}

bool ConnCliente::tryConnect(){
    this->m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_sockfd < 0){ printf("\n[CONN] erro abrindo socket"); }

    if(inet_addr(this->m_ip.c_str()) == -1){
        //Busca por nome
        struct hostent *he;
        struct in_addr **addr_list;
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( this->m_ip.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("\n[CONN] gethostbyname");
            printf("\n[CONN] Failed to resolve hostname\n");

            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            this->m_server.sin_addr = *addr_list[i];

            std::cout << "\n[CONN]" << this->m_ip <<" resolucao em "<< inet_ntoa(*addr_list[i])<< std::endl;

            break;
        }

    }else //plain ip this->m_ip
    {
        this->m_server.sin_addr.s_addr = inet_addr( this->m_ip.c_str() );
    }

    this->m_server.sin_family = AF_INET;
    this->m_server.sin_port = htons( this->m_port );

    //Connect to remote server
    if (connect(this->m_sockfd , (struct sockaddr *)&this->m_server , sizeof(this->m_server)) < 0) {
        perror("\n[CONN] falhou com o servidor");
        return false;
    }

    printf("\n[CONN] conectado OK");
    this->m_serverOn = true;

    return this->m_serverOn;

}

/**
 * Send data to the connected host
 */
bool ConnCliente::send_data(std::string data) {
    //Send some data
    if( send(this->m_sockfd , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("[CONN] Falhou no envio ");
        return false;
    }
    printf("\n[CONN] Enviado dados ao server");

    return true;
}

/**
 * Receive data from the connected host
 */
std::string ConnCliente::receive_data(int len=512) {
    char buffer[len];
    std::string reply;

    //Receive a reply from the server
    if( recv(this->m_sockfd , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("[CONN] Falhou no recv !");
    }

    reply = buffer;
    return reply;
}

void ConnCliente::teste(){
    std::string host;
    std::string port;

    std::cout<<"\n[TESTE] Digite o hostname : ";
    std::cin>>host;

    std::cout<<"\n[TESTE] Digite a porta : ";
    std::cin>>port;

    //connect to host
    ConnCliente cc(host , atoi(port.c_str()) );
    cc.tryConnect();

    //send some data
    std::string content = "CONNECT www.google.com:80 HTTP/1.1\r\nHost: www.google.com\r\nProxy-Connection: keep-alive\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nDNT: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:30.0) Gecko/20100101 Firefox/30.0\r\nProxy-Authorization: Basic MDM3MDE5NTE5MTg6c2VmYWNyZQ==\r\nAccept-Encoding: gzip, deflate,gzip, deflate\r\nContent-Type: text/html; charset=utf-8\r\nConnection: keep-alive\r\nExpect: 100-continue\r\n\r\n";
    std::cout << std::endl << content;
    cc.send_data( content );

    //receive and echo reply
    std::cout<<"----------------------------\n\n";
    std::cout<<cc.receive_data(1024);
    std::cout<<"\n\n----------------------------\n\n";

    getchar();
}

