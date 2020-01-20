#ifdef WIN32
#include "UtilWindows.h"
#endif // WIN32

#include "Util.h"
#include "Editbox21.h"

Editbox21::Editbox21(int x, int y, int l, int a, bool password) {
	this->x = x;
	this->y = y;
	this->l = l;
	this->a = a;
	this->password = password;

	//Defaults
	this->passwordChar = '*';
	this->tipoEstado = EB21_TE_NORMAL;
}

Editbox21::Editbox21(void)
{
}


Editbox21::~Editbox21(void)
{
}

std::string Editbox21::getTexto(){
	return this->texto;
}

bool Editbox21::isTextoEmpty(){
	return (this->texto.empty());
}

bool Editbox21::isTextoEmail(){
	return (this->texto.empty());
}

Editbox21 &Editbox21::setFonte(unsigned int fonte){
	this->fonte = fonte;
	return *this;
}

void Editbox21::desenha(){
	atualizaCorRGB();
	C2D2P_RetanguloPintado(this->x, this->y, this->l, this->a, 0,0,0);
	C2D2P_Retangulo(this->x, this->y, this->l, this->a, this->corR,this->corG,this->corB);

	std::string textoDisplay = "";
	if(isPassword()){
		Util::appendCharTam(textoDisplay, this->texto.length(), this->passwordChar);
	}else{
		textoDisplay = this->texto;
	}
	C2D2_DesenhaTexto(this->fonte, (this->x+this->l)/2, (this->y+this->a)/2, textoDisplay.c_str(), C2D2_TEXTO_CENTRALIZADO);

	//C2D2P_Retangulo(x, y, l, a, this->corR,this->corG,this->corB);
	//C2D2P_Linha(this->x, this->y, this->l, this->a, this->corR,this->corG,this->corB);
}

void Editbox21::setTipoEstado(int tipoEstado){
	this->tipoEstado = tipoEstado;
}

Editbox21 &Editbox21::setCorNormal(int corNormalR, int corNormalG, int corNormalB){
	this->corNormalR = corNormalR;
	this->corNormalG = corNormalG;
	this->corNormalB = corNormalB;
	return *this;
}

Editbox21 &Editbox21::setCorColisao(int corColisaoR, int corColisaoG, int corColisaoB){
	this->corColisaoR = corColisaoR;
	this->corColisaoG = corColisaoG;
	this->corColisaoB = corColisaoB;
	return *this;
}
Editbox21 &Editbox21::setCorEdicao(int corEdicaoR, int corEdicaoG, int corEdicaoB){
	this->corEdicaoR = corEdicaoR;
	this->corEdicaoG = corEdicaoG;
	this->corEdicaoB = corEdicaoB;
	return *this;
}

void Editbox21::atualizaCorRGB(){
	switch(this->tipoEstado){
	case EB21_TE_NORMAL:
		this->corR = corNormalR;
		this->corG = corNormalG;
		this->corB = corNormalB;
		break;
	case EB21_TE_COLISAO:
		this->corR = corColisaoR;
		this->corG = corColisaoG;
		this->corB = corColisaoB;
		break;
	case EB21_TE_EDICAO:
		this->corR = corEdicaoR;
		this->corG = corEdicaoG;
		this->corB = corEdicaoB;
		break;
	}
}

bool Editbox21::isPassword(){
	return this->password;
}
void Editbox21::atualiza(){
	if(this->tipoEstado == EB21_TE_EDICAO){
		C2D2_Botao *teclas = C2D2_PegaTeclas();
		C2D2_Mouse *mouse = C2D2_PegaMouse();

		do{
			this->texto += (teclas[C2D2_A].pressionado) ? "A" : "";
			this->texto += (teclas[C2D2_B].pressionado) ? "B" : "";
			this->texto += (teclas[C2D2_C].pressionado) ? "C" : "";
			this->texto += (teclas[C2D2_D].pressionado) ? "D" : "";
			this->texto += (teclas[C2D2_E].pressionado) ? "E" : "";
			this->texto += (teclas[C2D2_F].pressionado) ? "F" : "";
			this->texto += (teclas[C2D2_G].pressionado) ? "G" : "";
			this->texto += (teclas[C2D2_H].pressionado) ? "H" : "";
			this->texto += (teclas[C2D2_I].pressionado) ? "I" : "";
			this->texto += (teclas[C2D2_J].pressionado) ? "J" : "";
			this->texto += (teclas[C2D2_K].pressionado) ? "K" : "";
			this->texto += (teclas[C2D2_L].pressionado) ? "L" : "";
			this->texto += (teclas[C2D2_M].pressionado) ? "M" : "";
			this->texto += (teclas[C2D2_N].pressionado) ? "N" : "";
			this->texto += (teclas[C2D2_O].pressionado) ? "O" : "";
			this->texto += (teclas[C2D2_P].pressionado) ? "P" : "";
			this->texto += (teclas[C2D2_Q].pressionado) ? "Q" : "";
			this->texto += (teclas[C2D2_R].pressionado) ? "R" : "";
			this->texto += (teclas[C2D2_S].pressionado) ? "S" : "";
			this->texto += (teclas[C2D2_T].pressionado) ? "T" : "";
			this->texto += (teclas[C2D2_U].pressionado) ? "U" : "";
			this->texto += (teclas[C2D2_V].pressionado) ? "V" : "";
			this->texto += (teclas[C2D2_X].pressionado) ? "X" : "";
			this->texto += (teclas[C2D2_Y].pressionado) ? "Y" : "";
			this->texto += (teclas[C2D2_W].pressionado) ? "W" : "";
			this->texto += (teclas[C2D2_Z].pressionado) ? "Z" : "";
			this->texto += (teclas[C2D2_2].pressionado) ? "@" : "";
			this->texto += (teclas[C2D2_1].pressionado) ? "." : "";

			if(teclas[C2D2_ESPACO].pressionado){
				this->texto = this->texto.substr(0, this->texto.length()-1);
			}
			if(teclas[C2D2_ESC].pressionado){
				this->texto.clear();
			}

			desenha();
			C2D2_Sincroniza(C2D2_FPS_PADRAO);
		}while(!teclas[C2D2_ENTER].pressionado && !(mouse->botoes[C2D2_MESQUERDO].pressionado));

		this->tipoEstado = EB21_TE_NORMAL;
	}
}

bool Editbox21::colidiu(int x1b, int y1b, int l1b, int a1b){
	return C2D2_ColidiuQuadrados(this->x, this->y, this->l, this->a/3, x1b,y1b,l1b,a1b);
}
