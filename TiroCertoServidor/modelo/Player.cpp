#include "Player.h"

Player::Player()
{
    //ctor
}
Player::Player(std::string login, std::string senha, int credito){
    this->m_login = login;
    this->m_senha = senha;
	this->m_credito = credito;
}

Player::~Player()
{
    //dtor
}
