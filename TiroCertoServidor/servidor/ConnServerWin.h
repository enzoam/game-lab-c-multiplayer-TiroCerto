#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <thread>

#include "ClientSock.h"
#include "../protocolo/ProtocoloPartida.h"
#include "../banco/DBUsuario.h"
//#include "../modelo/Player.h"


class ConnServerWin
{
public:
	ConnServerWin(int port);
	ConnServerWin(void);
	~ConnServerWin(void);
	
	/*Aguarda as conexoes durante um tempo*/
    void startListening(int timeout);

	/*Pega conexoes*/
	void nextConnection();

	/*Identifica*/
	void identificaValidaCliente(ClientSock &sockComCliente, AutenticacaoRequest &autenticacaoRequest, AutenticacaoResponse& autenticacaoResponse, AutenticacaoHeader& autenticacaoHeader);
	/*Valida Login e Senha no banco*/
	void verificaUsuario(AutenticacaoRequest &autenticacaoRequest, Player &player);
	void insereUsuario(AutenticacaoRequest &autenticacaoRequest, Player &player);
	void getRanking(GameRanking &gameRanking);

    /*Get and Sets*/
    int getSockfd() { return m_sockfd; }
    void setSockfd(int sockfd) { m_sockfd = sockfd; }
    int getPort() { return m_port; }
    void setPort(int port) { m_port = port; }
    std::vector<ClientSock> getVecClientSock() { return m_vecClientSock; }
    void setVecClientSock(std::vector<ClientSock> clientSock) { m_vecClientSock = clientSock; }
    protected:
    private:
		bool jaExisteLinhaColuna(int &linha, int &coluna, std::vector<int> &totLinha, std::vector<int> &totColuna);
		void geraAlvoPlayers(GameAlvoPlayers &gameAlvoPlayers, std::vector<int> &totLinha, std::vector<int> &totColuna);

        int m_sockfd;
        int m_port;
        std::vector<ClientSock> m_vecClientSock;
		SOCKET principalSocket;
		bool waitStartGame;
		bool noAr;

		AutenticacaoResponse autenticacaoResponse;
		AutenticacaoRequest autenticacaoRequest;
		AutenticacaoHeader autenticacaoHeader;

		GamePlayers gamePlayers;
		GameAlvoPlayers gameAlvoPlayers;
		GameAlvoPlayer gameAlvoPlayer;
		GameAlvoPlayerResponse gameAlvoPlayerResponse;
		GameRanking gameRanking;
};

