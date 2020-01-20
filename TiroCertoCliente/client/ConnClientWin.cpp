#include "ConnClientWin.h"


ConnClientWin::ConnClientWin(std::string ip, int port) {
	this->m_ip = ip;
	this->m_port = port;
}

ConnClientWin::ConnClientWin(std::string serverconf){
	char content[20];
	std::ifstream infile;
	infile.open (serverconf);
	if (infile.is_open()) 	{
		if (infile.good()){
			infile.getline(content, 256, ',');
			this->m_ip = content;

			infile.getline(content, 256, ',');
			this->m_port = atoi(content);
		}
		infile.close();
	}
	else {
		printf("\n[CONN] Erro com o arquivo %s", serverconf.c_str());
	}
}

ConnClientWin::~ConnClientWin(void) {
	closesocket(this->principalSocket);
	WSACleanup();
}

int ConnClientWin::novoPlayer(Player &player){
	autenticacaoHeader.status = HEADER_NEWUSER;
	autenticacaoRequest.cabecalho = autenticacaoHeader;
	autenticacaoRequest.login = player.getLogin();
	autenticacaoRequest.senha = player.getSenha();

	int b = send(this->principalSocket, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0);
	printf("\n[CONN] Solicitacao de novo user, Bytes sent %d", b);

	recv(this->principalSocket, ((char *)&autenticacaoResponse), sizeof(autenticacaoResponse), 0);
	
	if((autenticacaoResponse.cabecalho.status != HEADER_ERROR) &&
		(autenticacaoResponse.cabecalho.status != AUTH_STATUS_ERROR)){
		player = autenticacaoResponse.player;
	}
	return autenticacaoResponse.mensagem;
}

int ConnClientWin::autenticaPlayer(Player &player){
	autenticacaoHeader.status = HEADER_CONNECT;
	autenticacaoRequest.cabecalho = autenticacaoHeader;
	autenticacaoRequest.login = player.getLogin();
	autenticacaoRequest.senha = player.getSenha();
	int codMsg = AUTH_MSG_VERIFICAUSER_ERROR;

	int b = send(this->principalSocket, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0);
	printf("\n[CONN] Solicitacao de login, Bytes sent %d", b);

	recv(this->principalSocket, ((char *)&autenticacaoResponse), sizeof(autenticacaoResponse), 0);
	
	if(autenticacaoResponse.cabecalho.status == AUTH_STATUS_OK){
		player = autenticacaoResponse.player;
	}
	codMsg = autenticacaoResponse.mensagem;
	
	return codMsg;
}

bool ConnClientWin::start(void){
	int r = 0;
	WSADATA wsaData;
	r = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(r != 0){
		printf("\n[CONN] Ocorreu erro ao registra a rede: " + WSAGetLastError());
	}

	this->principalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->principalSocket == INVALID_SOCKET) {
		printf("\n[CONN] Erro ao criar o socket: " + WSAGetLastError() );
		closesocket(this->principalSocket);
		return false;
	}

	//Endereco do SERVER
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_addr.s_addr = inet_addr( this->m_ip.c_str() ); //inet_addr(INADDR_ANY);//0.0.0.0 
	enderecoServidor.sin_port = htons( this->m_port );

}

bool ConnClientWin::tryAccept(){
	int iResult = connect( principalSocket, (SOCKADDR*) &enderecoServidor, sizeof(enderecoServidor) );
	printf( ("\n[CONN] Ocorreu erro ao registra a rede: " + std::to_string(WSAGetLastError())).c_str() );
	return (iResult > 0) || (iResult != SOCKET_ERROR);

	//sockaddr_in remetente;
	//int rementeSize = sizeof(remetente);
}

bool ConnClientWin::restart(void){
	closesocket(this->principalSocket);
	WSACleanup();
	return start();

}

int ConnClientWin::getPlayers(int &qtdeJogadores){
	gamePlayers.acao = GAME_ACAO_RECEBER_JOGADORES;
	gamePlayers.quantidade = 0;

	int codMsg = recv(this->principalSocket, ((char *)&gamePlayers), sizeof(gamePlayers), 0);
	if(gamePlayers.acao == GAME_ACAO_RECEBER_JOGADORES){
		qtdeJogadores = gamePlayers.quantidade;
	}

	printf("\n[SERVER]Recebido do servidor %d jogadores", qtdeJogadores);
	
	return codMsg;
}

int ConnClientWin::getAlvoPlayers(int &myPosAlvo, int totLinha[PLAYERS_MAX], int totColuna[PLAYERS_MAX]){
	gameAlvoPlayers.myPosAlvo = myPosAlvo;

	int codMsg = recv(this->principalSocket, ((char *)&gameAlvoPlayers), sizeof(gameAlvoPlayers), 0);
		myPosAlvo = gameAlvoPlayers.myPosAlvo;

		//Reapontando os valores
		for(int i=0; i<PLAYERS_MAX; i++){
			totLinha[i] = gameAlvoPlayers.totLinha[i];
			totColuna[i] = gameAlvoPlayers.totColuna[i];
		}
	
	return codMsg;
}

void ConnClientWin::getRanking(std::vector<Player> &players){
	autenticacaoHeader.status = HEADER_RANKING;
	autenticacaoRequest.cabecalho = autenticacaoHeader;
	gameRanking.quantidade = 8;

	int bSend = send(this->principalSocket, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0);
	int codMsg = recv(this->principalSocket, ((char *)&gameRanking), sizeof(gameRanking), 0);
	
	if(codMsg != SOCKET_ERROR){
		//Reapontando os valores
		for(int i=0; i< gameRanking.quantidade; ++i){
			players.push_back(Player(gameRanking.gameRankingInfo[i].login, "",  gameRanking.gameRankingInfo[i].credito ));
		}
	}
}

int ConnClientWin::sendAlvo(GameAlvoPlayer &gameAlvoPlayer){
	int bSent = send(this->principalSocket, ((char *)&gameAlvoPlayer), sizeof(gameAlvoPlayer), 0);
	return bSent;
}

int ConnClientWin::receiveAlvo(GameAlvoPlayerResponse &gameAlvoPlayerResponse){
	int codMsg = recv(this->principalSocket, ((char *)&gameAlvoPlayerResponse), sizeof(gameAlvoPlayerResponse), 0);
	return codMsg;
}