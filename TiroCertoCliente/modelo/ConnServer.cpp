#include "ConnServer.h"

#include <string.h> //bzero

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netdb.h> //gethostbyaddr
#include <arpa/inet.h>

ConnServer::ConnServer() {}

ConnServer::ConnServer(int port=12345) {
    this->m_port = port;
}

ConnServer::~ConnServer()
{
    close(this->m_sockfd);
}

void ConnServer::startListening() {
    char buffer[256];
    struct sockaddr_in serv_addr;
    int n;
    if (this->m_port < 0) {
        erroSair("\n[SERVER] Erro configurando uma porta");
    }

    this->m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_sockfd < 0){ erroSair("\n[SERVER] Erro iniciando socket"); }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->m_port);

     if (bind(this->m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        erroSair("\n[SERVER] Erro no binding da porta");
     }

/* //Winsocks.h
     char localhostName[80];
     gethostname(localhostName, sizeof(localhostName)){printf("\n[SERVER] Erro buscando nome local");}

     struct hostent *phe = gethostbyname(localhostName);
     if (phe == 0) {printf("\n[SERVER] Erro buscando IP do nome local");}

     //Todos os IPs
     for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        std::cout << "Address " << i << ": " << inet_ntoa(addr) << std::endl;
    }

    //Primeiro
    struct in_addr localhostIp;
    memcpy(&localhostIp, phe->h_addr_list[0], sizeof(struct in_addr));
*/

    struct ifreq ifr;
    struct sockaddr_in localhostIp;
    ifr.ifr_addr.sa_family = AF_INET;//IPv4
    strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);//eth?
    ioctl(this->m_sockfd, SIOCGIFADDR, &ifr);

    struct hostent *he;
    if ( (he = gethostbyaddr( &serv_addr, sizeof(serv_addr), AF_INET ) ) == NULL) {
        //gethostbyname failed
        herror("\n[SERVER] gethostbyaddr");
        printf("\n[CONN] Failed to resolve hostname\n");
    }

    //char localhostName = he[0].h_name;
    printf("\n[SERVER] Iniciado '%s' com IP '%s' e escutando na porta %i", he[0].h_name, inet_ntoa( ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr ), this->m_port);
    listen(this->m_sockfd,5);

}

