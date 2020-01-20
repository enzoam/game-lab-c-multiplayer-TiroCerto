#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta
{
    public:
        Carta();
        virtual ~Carta();
        unsigned int getValor() { return m_valor; }
        void setValor(unsigned int valor) { m_valor = valor; }
        unsigned char getLetra() { return m_letra; }
        void setLetra(unsigned char letra) { m_letra = letra; }
        std::string getDescricao() { return m_descricao; }
        void setDescricao(std::string descricao) { m_descricao = descricao; }
        std::string getSprite() { return m_sprite; }
        void setSprite(std::string sprite) { m_sprite = sprite; }
    protected:
    private:
        unsigned int m_valor;
        unsigned char m_letra;
        std::string m_descricao;
        std::string m_sprite;
};

#endif // CARTA_H
