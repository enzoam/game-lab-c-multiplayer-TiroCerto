#include "Cursor21.h"

bool AtualizaCursor21(Ator *a, unsigned int itMapa) {
	Evento evCursor;

	switch(a->estado.estado) {
	case ATOR_NASCENDO:
		// Muda para o estado adequado
		ATOR_TrocaEstado(a, CURSOR21_BRANCO, false);
		break;
	case CURSOR21_BRANCO:
		if(a->estado.subestado==ESTADO_INICIO) {
			ATOR_TrocaAnimacao(a, 0);
			// Troca o sub-estado
			a->estado.subestado=ESTADO_RODANDO;
		}
		while(ATOR_ProximoEvento(a, &evCursor)) {
			// se for um evento de movimentação
			switch(evCursor.tipoEvento)	{
			case EVT_PRESSIONOU_CIMA:
				ATOR_TrocaEstado(a, CURSOR21_BRANCO_CARREGANDO, false);
				break;
			}
		}
		break;
	case CURSOR21_VERDE:
			ATOR_TrocaAnimacao(a, 1);
			break;
	case CURSOR21_VERMELHO:
			ATOR_TrocaAnimacao(a, 2);
			break;
	case CURSOR21_MARELO:
			ATOR_TrocaAnimacao(a, 3);
			break;
	case CURSOR21_MARELO_PISCA:
			ATOR_TrocaAnimacao(a, 4);
			break;
	case CURSOR21_BRANCO_CARREGANDO:
			if(a->estado.subestado==ESTADO_INICIO){
				ATOR_TrocaAnimacao(a, 5);
				a->estado.subestado=ESTADO_RODANDO;
			}
			
			while(ATOR_ProximoEvento(a, &evCursor)) {
				// se for um evento de movimentação
				switch(evCursor.tipoEvento)	{
				case EVT_LIBEROU_CIMA:
					ATOR_TrocaEstado(a, CURSOR21_BRANCO, false);
					break;
				}
			}

			break;
	case CURSOR21_AMARELO_CARREGANDO:
			ATOR_TrocaAnimacao(a, 6);
			break;
	}
	return true;
}

Animacao animacaoCursor21[] = {
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	
	// Vetor do estado parado BRANCO
	{1, 1, {0}},

	// Vetor do estado parado VERDE
	{1, 1, {13}},

	// Vetor do estado parado VERMELHO
	{1, 1, {26}},

	// Vetor do estado parado AMARELO
	{1, 1, {27}},

	// Vetor do estado Pisca AMARELO
	{3, 6, {27, 40, 41}},

	// Vetor do estado BRANCO carregando
	{31, 4, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,13,13,13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,0}},

	// Vetor do estado AMARELO carregando
	{21, 4, {43, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 43,43,43,43,43,43,43,43,43}},
};

Ator* criaCursor21(int nLargura, int nAltura){
	if(!ATOR_CarregaAtorEstatico(CURSOR21, "./images/mira.png", 46, 46, 1,1, 0,0, animacaoCursor21, true,
		0, 0, &AtualizaCursor21)) {
		printf("\n[CURSOR] Erro carregando cursor animado");
	}
		
	// Cria o ator
	return ATOR_CriaAtor(CURSOR21, nLargura, nAltura, 90);
}