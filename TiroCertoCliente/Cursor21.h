#pragma once
#include <stdio.h>
#include "c2d2/ator.h"

enum {CURSOR21};
enum {CURSOR21_BRANCO=ATOR_PROG_INI, CURSOR21_VERDE, CURSOR21_VERMELHO, CURSOR21_MARELO, CURSOR21_MARELO_PISCA, CURSOR21_BRANCO_CARREGANDO, CURSOR21_AMARELO_CARREGANDO};

bool AtualizaCursor21(Ator *a, unsigned int itMapa);
Ator* criaCursor21(int nLargura, int nAltura);