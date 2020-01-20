#ifndef BARALHO_H
#define BARALHO_H

#include "Carta.h"
#include <vector>

class Baralho
{
    public:
        Baralho();
        virtual ~Baralho();
        std::vector<Carta> getCartas() { return m_cartas; }
        void setCartas(std::vector<Carta> vecCarta) { m_cartas = vecCarta; }

        /** Ao adicionar Carta, incluir na ordem (Menor -> Maior) */
        void addCarta(Carta carta);
    protected:
    private:
        std::vector<Carta> m_cartas; //!< Member variable "m_cartas"
};

#endif // BARALHO_H
