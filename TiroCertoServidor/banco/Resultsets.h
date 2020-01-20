/**
 * Resultsets utilizados pelo banco de dados
 */
#pragma once
#include <string>

struct DBUsuarioResultset{
	std::string login;
	std::string senha;
	int credito;
};
