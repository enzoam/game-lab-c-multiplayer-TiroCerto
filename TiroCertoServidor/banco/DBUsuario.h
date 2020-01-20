#include <stdio.h>
#include <string>
#include <vector>
#include "sqlite3.h"

#include "../modelo/Player.h"
#include "../banco/ConnSQLite.h"
#include "../banco/Resultsets.h"
#include "../util/Constantes.h"

#include "../protocolo/ProtocoloPartida.h"

class DBUsuario {
	public:
		DBUsuario();
		~DBUsuario();

		bool addUsuario(Player &player);
		bool delUsuario(Player &player);
		bool altUsuario(Player &player);
		bool extUsuario(std::string login, std::string senha, Player &player);
		bool relUsuario(std::vector<Player> &lstPlayers);

		bool addPontuacao(char nome[PLAYER_NOME_MAX], int pontuacao);
	private:
		static int extUsuarioCallback(void *NotUsed, int argc, char **argv, char **azColName);
		ConnSQLite* connSQLite;
};