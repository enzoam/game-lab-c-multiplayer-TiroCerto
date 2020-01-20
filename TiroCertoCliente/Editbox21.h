#pragma once
#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>
#include <string>

#define MAX_TAMANHO 50
#define EB21_TE_NORMAL 0
#define EB21_TE_COLISAO 1
#define EB21_TE_EDICAO 2

//Trabalha com a Chien
class Editbox21 {
private:
	std::string texto;		//Conteudo do edit
	int x,y, l,a;			//Dimensoes
	unsigned int fonte;		//Fonte de desenho

	bool password;		//Tipo campo de password
	char passwordChar;	//Char para o campo password

	int tipoEstado;

	int corNormalR, corNormalG, corNormalB;
	int corColisaoR, corColisaoG, corColisaoB;
	int corEdicaoR, corEdicaoG, corEdicaoB;
	int corR, corG, corB;
	void atualizaCorRGB();

public:
	Editbox21(int x, int y, int l, int a, bool password);
	Editbox21(void);
	~Editbox21(void);

	std::string getTexto();
	bool isTextoEmpty();
	bool isTextoEmail();

	//Desenha
	void desenha();

	//Verifica se foi clickado para edicao
	void atualiza();

	bool colidiu(int x1b, int y1b, int l1b, int a1b);

	void setTipoEstado(int tipoEstado);
	Editbox21 &setFonte(unsigned int fonte);

	Editbox21 &setCorNormal(int corNormalR, int corNormalG, int corNormalB);
	Editbox21 &setCorColisao(int corColisaoR, int corColisaoG, int corColisaoB);
	Editbox21 &setCorEdicao(int corEdicaoR, int corEdicaoG, int corEdicaoB);

	bool isPassword();
};

