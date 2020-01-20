#include "Baralho.h"

Baralho::Baralho()
{
    //ctor
}

Baralho::~Baralho()
{
    //dtor
}

void Baralho::addCarta(Carta carta) {
    m_cartas.push_back(carta);
}
