#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
    public:
        Player();
        Player(std::string login, std::string senha, int credito);
        virtual ~Player();
        std::string getSenha() { return m_senha; }
        void setSenha(std::string senha) { m_senha = senha; }
        std::string getLogin() { return m_login; }
        void setLogin(std::string login) { m_login = login; }
        int getCredito() { return m_credito; }
        void setCredito(int credito) { m_credito = credito; }
        int getPosicao() { return m_posicao; }
        void setPosicao(int posicao) { m_posicao = posicao; }
    protected:
    private:
        std::string m_senha;
        std::string m_login;
        int m_credito;
        int m_posicao;
};

#endif // PLAYER_H
