#pragma once
#include <stdio.h>
#include <WinSock2.h>

#include "c2d2/chien2d2.h"
#include "c2d2/chien2d2primitivas.h"
#include "c2d2/chienaudio2.h"

#include "Editbox21.h"
#include "Cursor21.h"
#include "protocolo\ProtocoloPartida.h"
#include "client\ConnClientWin.h"

class Menu
{
public:
	Menu(void);
	~Menu(void);

	static unsigned int spr_start_titulo;
	/*Cutscene*/
	void telaLogo(void);
	void start(void);
	
	/*Recursos de start*/
	int carregaRecursos(void);
	void iniciaRecursos(void);
	

	/*Tela de 'status servidor'
		- Status (conexao servidor)
		- Atualizar Status
		- Login
		- Novo Usuario
		-> Sobre (telaCreditos)
		x Sair
	*/
	void telaPrincipal(void);

	/*Tela de login
		- Usuario (txt)
		- Senha (txt)
		<- Voltar ('status servidor')
		-> Jogar
	*/
	void telaLogin(void);

		/*Tela de NovoUsuario
		- Usuario (txt)
		- Senha (txt)
		- Email (txt)
		<- Voltar ('status servidor')
		-> Cadastrar (conexao server)
	*/
	void telaNovoUsuario(void);

	/*Tela do jogo*/
	void telaJogo(void);
	
	/*Creditos*/
	void telaCreditos(void);

	/*Ranking*/
	void telaRanking(void);

private:
	// Indica se deve encerrar ou não a aplicação
	bool encerra;
	// Indica o estado atual (tela) do jogo
	// Valores:
	//      1 - Menu principal (status)
	//      2 - Login (para jogar)
	//      3 - Novo Usuario
	//      4 - Créditos (sobre)
	//		5 - Jogo( quando logado e conectado )
	int estadoatual;
	int fase_selecionada;

	// Recursos dos menus
	unsigned int fonte32; // Retorno da resposta do servidor

	unsigned int spr_titulo_statusservidor;
	unsigned int spr_titulo_login;
	unsigned int spr_titulo_novousuario;
	unsigned int spr_titulo_ranking;
	unsigned int spr_titulo_sobre;
	unsigned int spr_btn_voltar;
	unsigned int spr_btn_ok;
	unsigned int spr_btn_sair;
	unsigned int spr_btn_credito;
	unsigned int spr_btn_atualizar;
	unsigned int spr_txt_ranking;
	unsigned int spr_statusservidor_on;
	unsigned int spr_statusservidor_off;
	unsigned int spr_txt_login;
	unsigned int spr_txt_novousuario;
	unsigned int spr_txt_usuario;
	unsigned int spr_txt_senha;
	unsigned int spr_txt_email;
	unsigned int musica_fundo; //---------------------------------------------------
	
	Editbox21 ebUsuario;
	Editbox21 ebSenha;

	unsigned int spmira; //Mouse simples
	Ator *aCursor; //Mouse animado

	ConnClientWin *connClientWin;
	Player player;
	bool servidorDisponivel;

	GameAlvoPlayer gameAlvoPlayer;
	GameAlvoPlayerResponse gameAlvoPlayerResponse;

};

namespace
{
	int threadProxy( void *pointer )
	{
		try 
		{
			Menu &thMenu = *static_cast<Menu*>(pointer);
			thMenu.carregaRecursos();
			return 0;
		}
		catch( ... )
		{
			printf("\n[Exception] Erro na carga dos recursos");
			return 2;
		}
	}
}