#include <stdio.h>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "Resultsets.h"
#include "../modelo/Player.h"

class ConnSQLite {
	public:
		ConnSQLite(std::string pathBase);
		~ConnSQLite();

		bool executeSQL(std::string sql, int(*callback)(void *NotUsed, int argc, char **argv, char **azColName));
		bool selectSQL(std::string sql, DBUsuarioResultset& resultSet); //to do a ResultsetGenerico um dia
		bool selectSQList(std::string sql,  std::vector<Player> &lstPlayers);
	private:
		sqlite3 *base;
		std::string pathBase;
		int             rec_count;
		char *errMSG;
		const char      *tail;
};