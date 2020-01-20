#include "ConnSQLite.h"

ConnSQLite::ConnSQLite(std::string pathBase){
	this->rec_count = 0;
	this->pathBase = pathBase;
	int error = sqlite3_open(this->pathBase.c_str(), &this->base);
	if (error) 	{
		fprintf(stderr, "\n[DATABASE] Problemas no caminho da base: %s\n", 
							sqlite3_errmsg(this->base));
	}
}

ConnSQLite::~ConnSQLite(){
	//sqlite3_finalize( sqlite3_stmt );
	sqlite3_free(this->errMSG);
	sqlite3_close (this->base);
}

bool ConnSQLite::executeSQL(std::string sql, int(*callback)(void *NotUsed, int argc, char **argv, char **azColName)){
	bool ok = false;
	int error = sqlite3_exec(this->base, sql.c_str(), callback, 0, &this->errMSG);

	if(error){
		fprintf(stderr, "\n[DATABASE] Problemas na execucao do sql: %s\n", 
							sqlite3_errmsg(this->base));
	}else{
		printf("\n[DATABASE] Execucao do SQL realizado com sucesso!");
		ok = true;
	}

	return ok;
}
bool ConnSQLite::selectSQL(std::string sql, DBUsuarioResultset& resultSet){
	sqlite3_stmt *statement;
	bool result = false;
    if ( sqlite3_prepare(this->base, sql.c_str(), -1, &statement, 0 ) == SQLITE_OK )     {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )  {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) {
				resultSet.login = (char*)sqlite3_column_text(statement, 0);
				resultSet.senha = (char*)sqlite3_column_text(statement, 1);
				resultSet.credito = sqlite3_column_int(statement, 2);
                
				result = true;
				
				//for ( int i = 0; i < ctotal; i++ ) {
                    //std::string s = (char*)sqlite3_column_text(statement, i);
                    // print or format the output as you want 
                    //cout << s << " " ;
                //}
                //cout << endl;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR){
                //cout << "done " << endl;
                break;
            }    
        }
    }
	return result;
}

bool ConnSQLite::selectSQList(std::string sql, std::vector<Player> &lstPlayers){
	sqlite3_stmt *statement;
	bool result = false;
	Player player;
    if ( sqlite3_prepare(this->base, sql.c_str(), -1, &statement, 0 ) == SQLITE_OK )     {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )  {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) {
				player.setLogin( (char*)sqlite3_column_text(statement, 0) );
				player.setSenha( (char*)sqlite3_column_text(statement, 1) );
				player.setCredito( sqlite3_column_int(statement, 2) );
                
				lstPlayers.push_back(player);
				result = true;
				
				//for ( int i = 0; i < ctotal; i++ ) {
                    //std::string s = (char*)sqlite3_column_text(statement, i);
                    // print or format the output as you want 
                    //cout << s << " " ;
                //}
                //cout << endl;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR){
                //cout << "done " << endl;
                break;
            }    
        }
    }
	return result;
}
/**
 * SQLite Function Callback
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
*/