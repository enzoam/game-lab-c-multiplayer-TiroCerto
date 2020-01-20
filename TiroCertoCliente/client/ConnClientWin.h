#pragma once

#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../protocolo/ProtocoloPartida.h"
#include "../modelo/Player.h"


class ConnClientWin
{
public:
	ConnClientWin(std::string ip, int port);
	ConnClientWin(std::string serverconf);
	~ConnClientWin(void);

	/*TRUE caso rede ok*/
	bool start(void);
	bool restart(void);
	
	/*Aguarda as conexoes durante um tempo*/
	bool tryAccept();
    int novoPlayer(Player &player);
    int autenticaPlayer(Player &player);
	void receberAlvo(Player &player);
	void getRanking(std::vector<Player> &players);

	/*Retorna a quantidade de jogadores*/
	int getPlayers(int &qtdeJogadores);
	
	/*Preenche os alvos dos jogadores*/
	int getAlvoPlayers(int &myPosAlvo, int totLinha[PLAYERS_MAX], int totColuna[PLAYERS_MAX]);
	int sendAlvo(GameAlvoPlayer &gameAlvoPlayer);
	int receiveAlvo(GameAlvoPlayerResponse &gameAlvoPlayerResponse);
	
    protected:
    private:
        std::string m_ip;
        int m_port;
		SOCKET principalSocket;
		bool waitStartGame;

		AutenticacaoResponse autenticacaoResponse;
		AutenticacaoRequest autenticacaoRequest;
		AutenticacaoHeader autenticacaoHeader;
		sockaddr_in enderecoServidor;

		GamePlayers gamePlayers;
		GameAlvoPlayers gameAlvoPlayers;
		GameRanking gameRanking;

};

