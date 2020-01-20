#include "ConnServerWin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


ConnServerWin::ConnServerWin(void){}

ConnServerWin::ConnServerWin(int port=12345) {
    this->m_port = port;
	this->waitStartGame = true;

	//Registrando
	int r = 0;
	WSADATA wsaData;
	r = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(r != 0){
		erroSair("\n[SERVER] Erro ao registrar a rede: " + WSAGetLastError() );
	}
	noAr = true;
}

ConnServerWin::~ConnServerWin()
{
    //closesocket(this->m_sockfd);
	//TODO for no vector e closesocket em todos
	closesocket(this->principalSocket);
	WSACleanup();
}

void ConnServerWin::startListening(int timeout=60) {
	int tmpResp = 0;

	//Porta OK
	if ((this->m_port < 0) || (this->m_port > 65000)) {
        erroSair("\n[SERVER] Erro configurando uma porta");
    }

	//Criando socket
	this->principalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->principalSocket == INVALID_SOCKET) {
		erroSair("\n[SERVER] Erro ao criar o socket: " + WSAGetLastError() );
		closesocket(this->principalSocket);
	}

	//Endereco do SERVER
	sockaddr_in enderecoServidor;
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_addr.s_addr = (INADDR_ANY);//inet_addr("127.0.0.1"); //(INADDR_ANY);//0.0.0.0 
	enderecoServidor.sin_port = htons(this->m_port);

	//Endereco do SERVER
	tmpResp = bind(this->principalSocket, (SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor));
	if (tmpResp != 0) {
		erroSair("\n[SERVER] Socket nao aberto: " + WSAGetLastError() );
	}


	char localhostName[80];
    tmpResp = gethostname(localhostName, sizeof(localhostName));
	if (tmpResp != 0) {		printf("\n[SERVER] Erro buscando nome local");	}
    struct hostent *phe = gethostbyname(localhostName);
    if (phe == 0) {			printf("\n[SERVER] Erro buscando IP do nome local");}

     //Todos os IPs
     for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        std::cout << "\n[SOCKET INFO] Address " << i << ": " << inet_ntoa(addr) << std::endl;
    }

    //Primeiro
    struct in_addr localhostIp;
    memcpy(&localhostIp, phe->h_addr_list[0], sizeof(struct in_addr));


	tmpResp = listen(this->principalSocket, SOMAXCONN);
	if (tmpResp != 0) {
		erroSair("\n[SERVER] Socket com problemas: " + WSAGetLastError() );
	}
	printf("\n[SERVER] Iniciado com IP '%s' e escutando na porta %i",inet_ntoa(localhostIp), this->m_port);

	
	//Thread de conn
	std::thread clienteConn(&ConnServerWin::nextConnection, this);
	
	
	while(noAr){
			double timeInSeconds = 0;
			double timeInSecondsOld = 0;
			printf("\n[SERVER] O Jogo Iniciara em segundos ...",timeInSeconds);
			clock_t startTime = clock();
			do{
				clock_t endTime = clock();
				clock_t clockTicksTaken = endTime - startTime;
		
				if((int)timeInSeconds > (int)timeInSecondsOld){
					printf("%1.0f ",(int)timeout-timeInSeconds);
					timeInSecondsOld = timeInSeconds;
				}

				timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
		
			}while(timeInSeconds < timeout);
			this->waitStartGame = false;
			//clienteConn.join(); //Ultimo cliente pode ser q nao conecte

			if(m_vecClientSock.size() != 0){
				printf("\n[SERVER] Iniciando JOGO com %02d jogadores", m_vecClientSock.size());

				//Neste ponto os jogadores estao aguardando RECV
				//1. Retornar a quantidade d jogadores
				//2. Retornar os alvos dos jogadores
				gamePlayers.acao = GAME_ACAO_RECEBER_JOGADORES;
				gamePlayers.quantidade = m_vecClientSock.size();
				for(int i=0; i<m_vecClientSock.size(); i++){
					send(m_vecClientSock.at(i).sckCliente, ((char *)&gamePlayers), sizeof(gamePlayers), 0);
				}


				//Alvos nao podem se repetir
				std::vector<int> totLinha(m_vecClientSock.size());
				std::vector<int> totColuna(m_vecClientSock.size());
				geraAlvoPlayers(gameAlvoPlayers, totLinha, totColuna);
	
				for(int i=0; i<m_vecClientSock.size(); i++){
					gameAlvoPlayers.myPosAlvo = i;
					send(m_vecClientSock.at(i).sckCliente, ((char *)&gameAlvoPlayers), sizeof(gameAlvoPlayers), 0);
				}

				//Recebimento dos alvos
				int tempoMaisRapido = 500000;
				int posMaisRapido = 0;
				bool houveAcerto = false;
				int cPlayer =0;
				for(int i=0; i<m_vecClientSock.size(); i++){
					recv(m_vecClientSock.at(i).sckCliente, ((char *)&gameAlvoPlayer), sizeof(gameAlvoPlayer), 0);
		
					if(gameAlvoPlayer.acertou){
						houveAcerto=true;

						//Calculo do mais rapido
						if(tempoMaisRapido > gameAlvoPlayer.tempo){
							tempoMaisRapido = gameAlvoPlayer.tempo;
							posMaisRapido = cPlayer;
						}
					}
					cPlayer++;
				}			
				
				//Grava pontuacao do mais rapido em banco
				if(houveAcerto){
					DBUsuario user;
					user.addPontuacao(m_vecClientSock.at(posMaisRapido).nomePlayer, 10);

					//Houve mais rapido
					gameAlvoPlayerResponse.posAlvo = posMaisRapido;
					strcpy_s(gameAlvoPlayerResponse.login, m_vecClientSock.at(posMaisRapido).nomePlayer);
				}else{
					gameAlvoPlayerResponse.posAlvo = posMaisRapido;
					strcpy_s(gameAlvoPlayerResponse.login, "Todos erraram");
				}

				//Send do mais rapido/nenhum pros outros
				bool removePlayer = false;
				int count = 0;
				std::vector<int> vecRemover;
				for(std::vector<ClientSock>::iterator i = m_vecClientSock.begin(); i != m_vecClientSock.end(); ++i){
					
					int b = send(i->sckCliente, ((char *)&gameAlvoPlayerResponse), sizeof(gameAlvoPlayerResponse), 0);
					if(b == SOCKET_ERROR){
						closesocket(i->sckCliente);
						vecRemover.push_back(count);
					}
					count++;
				}

				//Desconectando clientes inativos
				if(!vecRemover.empty()){
					for(int i=0;i<vecRemover.size();++i){
						m_vecClientSock.erase(m_vecClientSock.begin()+i);
					}
				}
				
			}//if m_vecClientSock

	}//while

	getchar();
}

//posicao_tabuleiro[3+ rand () % 12][3+ rand () % 10]=3;
void ConnServerWin::geraAlvoPlayers(GameAlvoPlayers &gameAlvoPlayers, std::vector<int> &totLinha, std::vector<int> &totColuna){
	int nColuna;
	int nLinha;
	for(int i=0; i<m_vecClientSock.size()+PLAYERS_FALSO_MAX; i++){
		do{
			nColuna = (3+ rand () % 12);
			nLinha = (3+ rand () % 10);
		}while(jaExisteLinhaColuna(nLinha, nColuna, totLinha, totColuna));
		totLinha.push_back(nLinha);
		totColuna.push_back(nColuna);

		gameAlvoPlayers.totLinha[i] = nLinha;
		gameAlvoPlayers.totColuna[i] = nColuna;
	}
}

void ConnServerWin::nextConnection(){
	ClientSock csCliente;
	do{
		csCliente.sckCliente = INVALID_SOCKET;
		sockaddr_in tmpEnderecoCliente;

		int tamEnderecoCliente = sizeof(tmpEnderecoCliente);
		csCliente.sckCliente = accept(this->principalSocket, (SOCKADDR*)&tmpEnderecoCliente, &tamEnderecoCliente );
		if (csCliente.sckCliente == INVALID_SOCKET) {
			printf("[CONN] ACCEPT falhou: %d\n", WSAGetLastError());
			closesocket(this->principalSocket);
			WSACleanup();
			break;
		}
		
		//Copiando	
		csCliente.cli_addr = tmpEnderecoCliente;
		csCliente.sockaddr_t = tamEnderecoCliente;

		//if(waitStartGame){
			//Obtendo o IP e numero de clientes
			printf("\n[CONN] Novo CLIENTE [%02d] recepcionado [%s]", m_vecClientSock.size(), inet_ntoa(csCliente.cli_addr.sin_addr));
			//printf("\n[SERVER] ... contando ");

			//Identifica
			identificaValidaCliente(csCliente, autenticacaoRequest, autenticacaoResponse, autenticacaoHeader);

			//Testa adicao ao vetor
			if(autenticacaoResponse.cabecalho.status == AUTH_STATUS_OK){
				printf("\n[VALIDACAO] Identificado CLIENTE [%02d] adicionado [%s]", m_vecClientSock.size(), inet_ntoa(csCliente.cli_addr.sin_addr));
				m_vecClientSock.push_back(csCliente);
			
				//Devolvendo msg
				send(csCliente.sckCliente, ((char *)&autenticacaoResponse), sizeof(autenticacaoResponse), 0);

			}else if(autenticacaoResponse.cabecalho.status == AUTH_STATUS_RANKING){
				//Transforma para msg de ranking
				send(csCliente.sckCliente, ((char *)&gameRanking), sizeof(gameRanking), 0);
				closesocket(csCliente.sckCliente);
			}else{
				printf("\n[VALIDACAO] Erro CLIENTE [%02d] rejeitado [%s]", m_vecClientSock.size(), inet_ntoa(csCliente.cli_addr.sin_addr));
				//Devolvendo msg
				send(csCliente.sckCliente, ((char *)&autenticacaoResponse), sizeof(autenticacaoResponse), 0);
				closesocket(csCliente.sckCliente);
			}


		/*}else{

			//Jogo em andamento, ultima conexao se perde
			printf("\n[CONN] CLIENTE [%02d] rejeitado [%s]", m_vecClientSock.size()+1, inet_ntoa(csCliente.cli_addr.sin_addr));
			printf("\n[SERVER] Tentativa desconsiderada, jogo em andamento! ");

			recv(csCliente.sckCliente, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0);
			autenticacaoResponse.cabecalho.status = AUTH_STATUS_ERROR;
			autenticacaoResponse.mensagem = AUTH_MSG_EMANDAMENTO;
			send(csCliente.sckCliente, ((char *)&autenticacaoResponse), sizeof(autenticacaoResponse), 0);
		}*/

	}while(noAr);
	//Sleep(5000);
}


void ConnServerWin::identificaValidaCliente(ClientSock &sockComCliente, AutenticacaoRequest &autenticacaoRequest, AutenticacaoResponse& autenticacaoResponse, AutenticacaoHeader& autenticacaoHeader){
	if(recv(sockComCliente.sckCliente, ((char *)&autenticacaoRequest), sizeof(autenticacaoRequest), 0)) {
		printf("\n[DEBUG] Login: %s e Senha: %s", autenticacaoRequest.login.c_str(), autenticacaoRequest.senha.c_str());
		strcpy_s(sockComCliente.nomePlayer, autenticacaoRequest.login.c_str());
		
		switch (autenticacaoRequest.cabecalho.status){
		case HEADER_CONNECT :

			verificaUsuario(autenticacaoRequest, autenticacaoResponse.player);
			if(autenticacaoResponse.player.getPosicao() == 0){
				autenticacaoHeader.status = AUTH_STATUS_OK;
				autenticacaoResponse.cabecalho = autenticacaoHeader;
				autenticacaoResponse.mensagem = AUTH_MSG_VERIFICAUSER_OK;
			}else{
				autenticacaoHeader.status = AUTH_STATUS_ERROR;
				autenticacaoResponse.cabecalho = autenticacaoHeader;
				autenticacaoResponse.mensagem = AUTH_MSG_VERIFICAUSER_ERROR;
			}

			break;
		case HEADER_NEWUSER :
			
			insereUsuario(autenticacaoRequest, autenticacaoResponse.player);
			if(autenticacaoResponse.player.getPosicao() == 0){
				autenticacaoHeader.status = AUTH_STATUS_OK;
				autenticacaoResponse.cabecalho = autenticacaoHeader;
				autenticacaoResponse.mensagem = AUTH_MSG_CADASTRO_OK;
			}else{
				autenticacaoHeader.status = AUTH_STATUS_ERROR;
				autenticacaoResponse.cabecalho = autenticacaoHeader;
				autenticacaoResponse.mensagem = AUTH_MSG_CADASTRO_ERROR;
			}

			break;
		case HEADER_RANKING :
			autenticacaoHeader.status = AUTH_STATUS_RANKING;
			autenticacaoResponse.cabecalho = autenticacaoHeader;
			autenticacaoResponse.mensagem = AUTH_MSG_RANKING;
			getRanking(gameRanking);
			break;
		case HEADER_ERROR :
		default:
			break;

		}
		

	}
}

void ConnServerWin::verificaUsuario(AutenticacaoRequest &autenticacaoRequest, Player &player){
	if(	(autenticacaoRequest.login.length() > 0) &&
		(autenticacaoRequest.senha.length() > 0)
	){

		//Busca dados do usuario
		DBUsuario user;
		player.setLogin(autenticacaoRequest.login);
		player.setSenha(autenticacaoRequest.senha);

		player.setPosicao( user.extUsuario(autenticacaoRequest.login, autenticacaoRequest.senha, player) ? 0 : 1);

	}else{
		player.setPosicao(-1);
	}
}

void ConnServerWin::insereUsuario(AutenticacaoRequest &autenticacaoRequest, Player &player){
	if(	(autenticacaoRequest.login.length() > 0) &&
		(autenticacaoRequest.senha.length() > 0)
	){

		DBUsuario user;
		player.setLogin(autenticacaoRequest.login);
		player.setSenha(autenticacaoRequest.senha);
		player.setCredito(JOGO_CREDITO_INICIAL);
		player.setPosicao( user.addUsuario(player) ? 0 : 1);
		
	}else{
		player.setPosicao(-1);
	}
}

void ConnServerWin::getRanking(GameRanking &gameRanking){
	std::vector<Player> lstPlayers;
	DBUsuario user;
	user.relUsuario(lstPlayers);
	int counter = 0;
	for(std::vector<Player>::iterator it = lstPlayers.begin(); it != lstPlayers.end(); ++it){
		strcpy_s(gameRanking.gameRankingInfo[counter].login, it->getLogin().c_str());
		gameRanking.gameRankingInfo[counter].credito = it->getCredito();
		counter++;
	}
	gameRanking.quantidade = counter;
}

bool ConnServerWin::jaExisteLinhaColuna(int &linha, int &coluna, std::vector<int> &totLinha, std::vector<int> &totColuna){
	
	for (int i=0; i < totLinha.size(); i++) {
		for (int j=0; j < totColuna.size(); j++) {
			if( (totLinha[i] == linha) &&
				(totColuna[i] == coluna)
			){
				return true;
			}
		}
	}
	return false;
}