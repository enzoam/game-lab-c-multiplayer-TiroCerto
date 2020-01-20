#ifndef PROTOCOLOPARTIDA_H_INCLUDED
#define PROTOCOLOPARTIDA_H_INCLUDED

#include "../modelo/Player.h"
#include <string>
#include <vector>

#define PLAYERS_MAX  100
#define PLAYER_NOME_MAX		50
#define PLAYERS_FALSO_MAX	5

#define HEADER_CONNECT  100
#define HEADER_ERROR    101
#define HEADER_NEWUSER  102
#define HEADER_RANKING  103

#define AUTH_STATUS_OK      200
#define AUTH_STATUS_ERROR   201
#define AUTH_STATUS_CONNECT 202
#define AUTH_STATUS_RANKING 203

#define AUTH_MSG_VERIFICAUSER_OK	300 //"Bem vindo ao jogo"
#define AUTH_MSG_VERIFICAUSER_ERROR 301 //"Usuarios ou Senha invalidos !"
#define AUTH_MSG_CADASTRO_OK		302 //"Cadastro realizado com sucesso."
#define AUTH_MSG_CADASTRO_ERROR		303 //"Nao foi possivel cadastrar jogador"
#define AUTH_MSG_EMANDAMENTO		304 //"Nao foi possivel entrar no jogo agora"
#define AUTH_MSG_RANKING			305 //"Ranking ok"

#define GAME_ACAO_EXIT              0   //Sair quando nao tiver valor da mesa
#define GAME_ACAO_RECEBER_JOGADORES 1   //Quantidade de jogadores
#define GAME_ACAO_RECEBER_ALVOS     2	// Alvos gerados pelo servidor


#define GAME_INFO_PLAYERS           0   //Info dos player que estao na banca

struct AutenticacaoHeader {
    int status;
};
struct AutenticacaoRequest{
    AutenticacaoHeader cabecalho;
    std::string login;
    std::string senha;
};
struct AutenticacaoResponse{
    AutenticacaoHeader cabecalho;
    Player player;
    int mensagem;
};

/*Etapa 1 - Receber quantidade de jogadores*/
struct GamePlayers{
    int acao;
    int quantidade;
};

/*Alvo dos jogadores*/
struct GameAlvoPlayers{
	int myPosAlvo;
	int totLinha[PLAYERS_MAX];
	int totColuna[PLAYERS_MAX];
};

/*Alvo do player*/
struct GameAlvoPlayer{
	bool acertou;
	int tempo;
	int linha;
	int coluna;
};

struct GameAlvoPlayerResponse{
    int posAlvo;/*codigo do jogador que acertou antes*/
	char login[PLAYER_NOME_MAX];
};

struct GameRankingInfo{
   char login[PLAYER_NOME_MAX];
   int credito;
};

struct GameRanking{
   	GameRankingInfo gameRankingInfo[PLAYERS_MAX];
	int quantidade;
};

#endif // PROTOCOLOPARTIDA_H_INCLUDED
