#include "DBUsuario.h"

DBUsuario::DBUsuario(){
	connSQLite = new ConnSQLite( JOGO_BASE_DADOS );
}

DBUsuario::~DBUsuario(){
}

bool DBUsuario::addUsuario(Player &player){
	char buffer[10];
	_itoa_s(JOGO_CREDITO_INICIAL, buffer, 10);
	return connSQLite->executeSQL("INSERT INTO usuario VALUES (\""+player.getLogin()+"\", \""+player.getSenha()+"\", " +buffer+")",  nullptr);
}

bool DBUsuario::delUsuario(Player &player){
	return connSQLite->executeSQL("DELETE usuario WHERE login=\""+player.getLogin()+"\" AND senha=\""+player.getSenha()+"\"",  nullptr);
}
bool DBUsuario::altUsuario(Player &player){return false;}
bool DBUsuario::addPontuacao(char nome[PLAYER_NOME_MAX], int pontuacao){
	char sql[255];
	sprintf_s(sql, "UPDATE usuario SET credito=credito+%d WHERE login=\"%s\"", pontuacao, nome);
	return connSQLite->executeSQL(sql,  nullptr);
}

bool DBUsuario::extUsuario(std::string login, std::string senha, Player &player){
	DBUsuarioResultset rsUsuario;
	bool ok = connSQLite->selectSQL("SELECT login, senha, credito FROM usuario WHERE login=\""+login+"\" AND senha=\""+senha+"\"",  rsUsuario);
	if(ok){
		player.setLogin(rsUsuario.login);
		player.setSenha(rsUsuario.senha);
		player.setCredito(rsUsuario.credito);
	}

	return ok;
}

bool DBUsuario::relUsuario(std::vector<Player> &lstPlayers){
	return connSQLite->selectSQList("SELECT login, senha, credito FROM usuario ORDER BY credito DESC", lstPlayers);
}

 int DBUsuario::extUsuarioCallback(void *NotUsed, int argc, char **argv, char **azColName){
  if(argc) {
    printf("\n[DATABASE] %s = %s\n", azColName[0], argv[0] ? argv[0] : "NULL");


  }
  return 0;
}