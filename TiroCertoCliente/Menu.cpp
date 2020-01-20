#include "Menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "SDL/SDL_thread.h"
#include "jogo_constantes.h"
#include "c2d2/chien2d2.h"
#include "c2d2/chienaudio2.h"
#include "c2d2/chien2d2primitivas.h"
#include "c2d2/ator.h"
#include "c2d2/chien2d2mapa.h"


unsigned int Menu::spr_start_titulo;

Menu::Menu(void)
{
	encerra=false;
	estadoatual=1;

	// Recursos do jogo
	fonte32=0;
	Menu::spr_start_titulo=0;
	spr_titulo_statusservidor=0;
	spr_titulo_login=0;
	spr_titulo_novousuario=0;
	spr_titulo_ranking=0;
	spr_titulo_sobre=0;
	spr_btn_voltar=0;
	spr_btn_ok=0;
	spr_btn_sair=0;
	spr_btn_credito=0;
	spr_btn_atualizar=0;
	spr_txt_ranking=0;
	spr_statusservidor_on=0;
	spr_statusservidor_off=0;
	spr_txt_login=0;
	spr_txt_novousuario=0;
	spr_txt_usuario=0;
	spr_txt_senha=0;
	spr_txt_email=0;

	servidorDisponivel = false;

	//declara musicas //---------------------------------------------------
	musica_fundo=0;	//---------------------------------------------------

	//ebUsuario=Properties.loadFile().usuario;
	//ebSenha=0; //Properties.loadFile().ebSenha
	//ebEmail=0; //Properties.loadFile().ebEmail

	spmira=0;
	aCursor=0;
}

Menu::~Menu(void)
{
	    // faz a tela de descarregamento
    if(fonte32!=0)
    {
        C2D2_TrocaCorLimpezaTela(0,0,0);
        C2D2_LimpaTela();
        C2D2_DesenhaTexto(fonte32, 400, 284, "Encerrando. Por favor, aguarde.", C2D2_TEXTO_CENTRALIZADO);
        C2D2_Sincroniza(C2D2_FPS_PADRAO);
    }
    // Apaga tudo, se for 0 a biblioteca ignora
    C2D2_RemoveFonte(fonte32);
	C2D2_RemoveSpriteSet(Menu::spr_start_titulo);
	C2D2_RemoveSpriteSet(spr_titulo_statusservidor);
	C2D2_RemoveSpriteSet(spr_titulo_login);
	C2D2_RemoveSpriteSet(spr_titulo_novousuario);
	C2D2_RemoveSpriteSet(spr_titulo_ranking);
	C2D2_RemoveSpriteSet(spr_titulo_sobre);
	C2D2_RemoveSpriteSet(spr_btn_voltar);
	C2D2_RemoveSpriteSet(spr_btn_ok);
	C2D2_RemoveSpriteSet(spr_txt_ranking);
	C2D2_RemoveSpriteSet(spr_btn_sair);
	C2D2_RemoveSpriteSet(spr_btn_credito);
	C2D2_RemoveSpriteSet(spr_btn_atualizar);
	C2D2_RemoveSpriteSet(spr_statusservidor_on);
	C2D2_RemoveSpriteSet(spr_statusservidor_off);
	C2D2_RemoveSpriteSet(spr_txt_login);
	C2D2_RemoveSpriteSet(spr_txt_novousuario);
	C2D2_RemoveSpriteSet(spr_txt_usuario);
	C2D2_RemoveSpriteSet(spr_txt_senha);
	//C2D2_RemoveSpriteSet(spr_txt_email);
}

// Start:
//      1 - Menu principal (status)
//      2 - Login (para jogar)
//      3 - Novo Usuario
//      4 - Créditos (sobre)
//		5 - Jogo( quando logado e conectado )
//		6 - Ranking
void Menu::start() {
	iniciaRecursos();

	//Logo
	//SDL_Thread *thread;
    //thread = SDL_CreateThread(&threadProxy,this);

	carregaRecursos();
	telaLogo();

	aCursor = criaCursor21(0, 0);

    // Carrega os recursos e testa se pode continuar (se carregou tudo certo)
    if(true) {
		//SDL_WaitThread(thread, NULL);

		do
	    {
            switch(estadoatual)
            {
                case 1:
                    telaPrincipal();
                    break;
                case 2:
					telaLogin();
                    break;
                case 3:
                    telaNovoUsuario();
                    break;
				case 4:
                    telaCreditos();
                    break;
				case 5:
                    telaJogo();
                    break;
				case 6:
                    telaRanking();
                    break;
                default:
                    // Deu erro, encerra
                    encerra=true;
                    break;
            }
	    }
	    while(!encerra);
    }

	free(aCursor);
	ATOR_DescarregaAtor(CURSOR21);

	ATOR_Encerra();

	// Encerra a Chien Audio 2
	CA2_Encerra();
	// Encerra a Chien2D 2
	C2D2_Encerra();
}

int Menu::carregaRecursos(void)
{
	int erroCarga = 0;

    // Carrega a fonte tamanho 32. Para cada recurso carregado, testamos se ele foi carregado corretamente
    fonte32 = C2D2_CarregaFonte(IMAGES_DIR "arial32.png", 32);
    if(fonte32==0){ printf("\n[Load]Falhou carregar a fonte de tamanho 32.\n");}

    // Como já tem uma fonte carregada, pode fazer a tela de load
    //C2D2_TrocaCorLimpezaTela(0,0,0);
    //C2D2_LimpaTela();
    C2D2_DesenhaTexto(fonte32, 400, 284, "Carregando. Por favor, aguarde.", C2D2_TEXTO_CENTRALIZADO);
	C2D2_Sincroniza(C2D2_FPS_PADRAO);

	// Continua carregando os recursos
	spr_titulo_statusservidor = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_titulo_statusservidor.png", 800,84);
    if(spr_titulo_statusservidor==0){ printf("\n[Load] Falhou carregar spr_titulo_statusservidor"); erroCarga = 1;}

	spr_titulo_login = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_titulo_login.png", 800,84);
    if(spr_titulo_login==0){ printf("\n[Load] Falhou carregar spr_titulo_login"); erroCarga = 1;}

	spr_titulo_novousuario = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_titulo_novousuario.png", 800,84);
    if(spr_titulo_novousuario==0){ printf("\n[Load] Falhou carregar spr_titulo_novousuario"); erroCarga = 1;}

	spr_titulo_ranking = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_titulo_ranking.png", 800,84);
    if(spr_titulo_ranking==0){ printf("\n[Load] Falhou carregar spr_titulo_ranking"); erroCarga = 1;}

	spr_titulo_sobre = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_titulo_sobre.png", 800,84);
    if(spr_titulo_sobre==0){ printf("\n[Load] Falhou carregar spr_titulo_sobre"); erroCarga = 1;}

	spr_btn_voltar = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_btn_voltar.png", 100,100);
    if(spr_btn_voltar==0){ printf("\n[Load] Falhou carregar spr_btn_voltar"); erroCarga = 1;}

	spr_btn_ok = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_btn_ok.png", 100,100);
    if(spr_btn_ok==0){ printf("\n[Load] Falhou carregar spr_btn_ok"); erroCarga = 1;}

	spr_txt_ranking = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_ranking.png", 240,70);
    if(spr_txt_ranking==0){ printf("\n[Load] Falhou carregar spr_txt_ranking"); erroCarga = 1;}

	spr_btn_sair = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_btn_sair.png", 100,100);
    if(spr_btn_sair==0){ printf("\n[Load] Falhou carregar spr_btn_sair"); erroCarga = 1;}

	spr_btn_credito = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_btn_credito.png", 100,100);
    if(spr_btn_credito==0){ printf("\n[Load] Falhou carregar spr_btn_credito"); erroCarga = 1;}

	spr_btn_atualizar = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_btn_atualizar.png", 74,74);
    if(spr_btn_atualizar==0){ printf("\n[Load] Falhou carregar spr_btn_atualizar"); erroCarga = 1;}

	spr_statusservidor_on = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_statusservidor_on.png", 77,24);
    if(spr_statusservidor_on==0){ printf("\n[Load] Falhou carregar spr_statusservidor_on"); erroCarga = 1;}

	spr_statusservidor_off = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_statusservidor_off.png", 212,24);
    if(spr_statusservidor_off==0){ printf("\n[Load] Falhou carregar spr_statusservidor_off"); erroCarga = 1;}

	spr_txt_login = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_login.png", 215,70);
    if(spr_txt_login==0){ printf("\n[Load] Falhou carregar spr_txt_login"); erroCarga = 1;}

	spr_txt_novousuario = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_novousuario.png", 340,70);
    if(spr_txt_novousuario==0){ printf("\n[Load] Falhou carregar spr_txt_novousuario"); erroCarga = 1;}

	spr_txt_usuario = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_usuario.png", 357,70);
    if(spr_txt_usuario==0){ printf("\n[Load] Falhou carregar spr_txt_usuario"); erroCarga = 1;}

	spr_txt_senha = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_senha.png", 294,70);
    if(spr_txt_senha==0){ printf("\n[Load] Falhou carregar spr_txt_senha"); erroCarga = 1;}

	//spr_txt_email = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_txt_email.png", 285,70);
    //if(spr_txt_email==0){ printf("\n[Load] Falhou carregar spr_txt_email"); erroCarga = 1;}

    spmira = C2D2_CarregaSpriteSet(IMAGES_DIR "mira.png", 46,46);
    if(spmira==0){ printf("\n[Load] Falhou carregar o sprite da mira."); erroCarga = 1; }

	//carrega musica //---------------------------------------------------
	musica_fundo = CA2_CarregaMusica("./sons/TelaPrincipal.wav"); //-------------------------------------------------

    // Se chegou até aqui, carregou tudo 100%
    return erroCarga;
}
void Menu::iniciaRecursos(){

	// Deixa os números aleatórios a cada vez que o programa roda
	srand(time_t(0));
	// Inicia a Chien2D 2 e testa se deu tudo certo
	if(C2D2_Inicia(LARGURA_TELA, ALTURA_TELA, C2D2_JANELA, C2D2_DESENHO_OPENGL, GAMENOMEVERSAO))
		printf("\n[CHIEN] Iniciou a Chien2D 2 com sucesso");
	else {
		printf("\n[CHIEN] Falhou ao iniciar a Chien2D 2. Encerrando o programa.");
	}
	// Inicia as primitivas
	C2D2P_Inicia();
	// Inicia o sistema de áudio. Deve ser feito obrigatoriamente após iniciar a Chien2D 2
	if(CA2_Inicia())
		printf("\n[CHIEN] Sistema de audio iniciado corretamente. O jogo vai rodar com sons e musica.");
	else
		printf("\n[CHIEN] Nao foi possivel iniciar o sistema de audio. Vai rodar sem som e musicas :( ...");

	ATOR_Inicia();

	//Recursos de rede
	this->connClientWin = new ConnClientWin("server.conf");
	this->connClientWin->start();
	servidorDisponivel = connClientWin->tryAccept();

}

void Menu::telaLogo(){
	printf("\n[LOGO] Iniciando logo");
	C2D2_TrocaCorLimpezaTela(0, 0, 0);
	C2D2_Botao *teclas = C2D2_PegaTeclas();
	C2D2_Mouse *mouse = C2D2_PegaMouse();

	int spr_start_titulo_WIDTH = 600;
	int spr_start_titulo_HEIGHT = 304;

	//Carregando logo
    Menu::spr_start_titulo = C2D2_CarregaSpriteSet(IMAGES_DIR "spr_start_titulo.png", spr_start_titulo_WIDTH, spr_start_titulo_HEIGHT);
    if(Menu::spr_start_titulo==0){ printf("\n[Load] Falhou carregar spr_start_titulo");}

	int tempo = 0;
	do {
		C2D2_LimpaTela();

		// Desenha logo
		C2D2_DesenhaSprite(Menu::spr_start_titulo,
			0, (LARGURA_TELA/2)-(spr_start_titulo_WIDTH/2),ALTURA_TELA/2-(spr_start_titulo_HEIGHT/2));

		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}while(tempo++<300 && !teclas[C2D2_ENCERRA].pressionado && !teclas[C2D2_ESC].pressionado && !teclas[C2D2_ENTER].pressionado && !mouse->botoes[C2D2_MESQUERDO].pressionado);
	printf("\n[LOGO] Finalizado logo");

}

void Menu::telaPrincipal()
{
	// Toca música //---------------------------------------------------
	CA2_TocaMusica(musica_fundo, -1); //---------------------------------------------------

	// Recupera o teclado
	C2D2_Botao *teclas = C2D2_PegaTeclas();
    C2D2_Mouse *mouse = C2D2_PegaMouse();
	static Evento evCursor;

    // Variáveis para os botões, 1 se o mouse está em cima, 0 caso contrário
    int bspr_btn_atualizar=0, bspr_txt_login=0, bspr_txt_novousuario=0, bspr_btn_sair=0, bspr_btn_credito=0, bspr_txt_ranking;

    // Sincroniza para atualizar o teclado
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	do {

		//TODO Mudar para o loading
		if(teclas[C2D2_CIMA].pressionado)	{
			evCursor.tipoEvento = EVT_PRESSIONOU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}
		if(teclas[C2D2_CIMA].liberado)	{
			evCursor.tipoEvento = EVT_LIBEROU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}

        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            encerra=true;
        // Vê se o mouse está em cima de um botão e atualiza o estado
        bspr_btn_atualizar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_atualizar, 0, 150,100)) ? 1 : 0 ;
		bspr_txt_login = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_txt_login, 0,  (LARGURA_TELA/2)-107,240)) ? 1 : 0 ;
		bspr_txt_novousuario = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_txt_novousuario, 0, (LARGURA_TELA/2)-(170),330)) ? 1 : 0 ;
		bspr_txt_ranking = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_txt_ranking, 0, (LARGURA_TELA/2)-(120),420)) ? 1 : 0 ;

		bspr_btn_sair = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_sair, 0, 10,470)) ? 1 : 0 ;
		bspr_btn_credito = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_credito, 0, LARGURA_TELA-100-10,470)) ? 1 : 0 ;

        // Se o botão do mouse está pressionado, toma uma ação
        if(mouse->botoes[C2D2_MESQUERDO].pressionado) {
            // O botão ativo é o botão da ação equivalente
            if(bspr_btn_sair==1){
				encerra=true; //Sair
			}else if(bspr_txt_login==1){
                estadoatual=2; //Login
			}else if(bspr_txt_novousuario==1){
                estadoatual=3; //NovoUser
			}else if(bspr_txt_ranking==1){
				if(servidorDisponivel){
					estadoatual=6; //Credito(4) //Ranking(6) 
				}else{servidorDisponivel = connClientWin->tryAccept();}
			}else if(bspr_btn_credito==1){
				estadoatual=4; //Credito(4)

			}else if((bspr_btn_atualizar==1) && !servidorDisponivel){
				servidorDisponivel = connClientWin->tryAccept();
			}
        }

        // Limpa a tela e desenha
		ATOR_Atualiza(aCursor, 0);
		ATOR_AplicaEstado(aCursor, 0, 0, 0);
		C2D2_LimpaTela();

		//Titulo
        C2D2_DesenhaSprite(spr_titulo_statusservidor, 0, 0, 0);

		// Desenha os botões de acordo com o estado
        C2D2_DesenhaSprite(spr_btn_atualizar, bspr_btn_atualizar, 150, 100);
		C2D2_DesenhaSprite(servidorDisponivel ? spr_statusservidor_on : spr_statusservidor_off, 0, 150+150, 130);
		
		C2D2_DesenhaSprite(spr_txt_login, bspr_txt_login, (LARGURA_TELA/2)-107, 240);
		C2D2_DesenhaSprite(spr_txt_novousuario, bspr_txt_novousuario, (LARGURA_TELA/2)-170, 330);
		C2D2_DesenhaSprite(spr_txt_ranking, bspr_txt_ranking, (LARGURA_TELA/2)-120, 420);

		C2D2_DesenhaSprite(spr_btn_sair, bspr_btn_sair, 10, 470);
		C2D2_DesenhaSprite(spr_btn_credito, bspr_btn_credito, LARGURA_TELA-100-10, 470);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);

		ATOR_Desenha(aCursor, 0, mouse->x, mouse->y);

		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	while(!encerra && estadoatual==1);
}

void Menu::telaJogo()
{

	// Carrega musica de fundo //------------------------------------------------------------------
	musica_fundo = CA2_CarregaMusica("./sons/level1.wav");//-----------------------------------------------------------------
	CA2_TocaMusica(musica_fundo, -1);//-----------------------------------------------------------------
	
	unsigned int level1background = C2D2_CarregaSpriteSet("./imagens/MAPA1.png", 800, 600);
	
	// Carrega unidades inimigas
	unsigned int carregador = C2D2_CarregaSpriteSet("./imagens/carregador.png", 32, 32);

	unsigned int alvo1 = C2D2_CarregaSpriteSet("./imagens/alvo1.png", 32, 32);
	unsigned int alvo1Acerto = C2D2_CarregaSpriteSet("./imagens/alvo1.png", 32, 32);
	
	unsigned int alvo2 = C2D2_CarregaSpriteSet("./imagens/alvo2.png", 32, 32);
	unsigned int alvo2Acerto = C2D2_CarregaSpriteSet("./imagens/alvo2.png", 32, 32);

	unsigned int ChanceUtilizada = C2D2_CarregaSpriteSet("./imagens/ChanceUtilizada.png", 32, 32);
	unsigned int ChanceUtilizadaAtaque = CA2_CarregaEfeito("./sons/ChanceUtilizadaAtaque.ogg");

	// Carrega ponteiro do mouse / arma
	unsigned int ponteiroMouse = C2D2_CarregaSpriteSet("./imagens/Cursor.png", 32, 32);
	unsigned int DestruidoAlvo = CA2_CarregaEfeito("./sons/DestruidoAlvo.ogg");
	unsigned int PerdidoAlvo = CA2_CarregaEfeito("./sons/PerdidoAlvo.ogg");
	
	unsigned int SemTiro = CA2_CarregaEfeito("./sons/GUNAIR2.WAV");

	unsigned int Tiro[6] =	{CA2_CarregaEfeito("./sons/GUNZING1.WAV"),
					CA2_CarregaEfeito("./sons/GUNZING2.WAV"),
					CA2_CarregaEfeito("./sons/GUNZING3.WAV"),
					CA2_CarregaEfeito("./sons/GUNZING4.WAV"),
					CA2_CarregaEfeito("./sons/GUNZING5.WAV"),
					CA2_CarregaEfeito("./sons/GUNZING6.WAV")};


	// Anima Alvo
	int quadrosIni[4] = {0, 1, 2, 1};
	int quadroAtualIni = 0;
	int tempoQuadroIni = 10;
	int qAlvos[2] = {alvo1, alvo2};
	int quadrosDestruido[1] = {6};
	int quadroAtualDestruido = 0;
	int tempoQuadroDestruido = 10;
	int qAlvosDestruido[2] = {alvo1, alvo2};

	// Anima Marcadpr de Chance Utilizada
	int quadrosDefChanceUtilizada[4] = {6, 7, 8, 6};
	int quadroAtualDefChanceUtilizada = 0;
	int tempoQDefChanceUtilizada = 20;
	int quadroDefChanceUtilizada = 0;

	// Anima Criador de Itens
	int quadrosDefcarregador[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	int quadroDefcarregador = 0;
	int temporizacarregador = 0;
	
	//contagem de alvos
	int conta_Alvos=0;

	// Número de Chances do jogador
	int Chances = 10;

	int AlvosAcertos = 0;

	bool perdeu = false;
	C2D2_Botao *teclas = C2D2_PegaTeclas();
	clock_t tempoInicioSaque = 0;

	do
	{
		//dividida a tela em pedaços de 32pxs 800 x 600 e limpa a tela
		int posicao_tabuleiro[24][17];
		int i = 1;
		int j = 1;
		for (i=1;i<24;i++){
			for (j=1;j<17;j++){
				posicao_tabuleiro[i][j]=0;
			}
		}
		//variaveis que determinarao a posicao do mouse em relação ao grid criado
		int mouseposicaocol=0;
		int mouseposicaolin=0;
		
		C2D2_LimpaTela();

		// Recupera comandos do mouse
		C2D2_Mouse *mouse = C2D2_PegaMouse();
		// Variaveis para uso do mouse
		int xmouse, ymouse;

		int indice_tiro=1;
		int alvo_perdido=0;
		int alvo_destruido=0;	
		int ArmaCarregada=0;

		int tempo_limite = 5;

		time_t now = time(0);


		/*COMO USAR A ENGINE DE CRIAÇÃO

			O MAPA TEM 16 COLUNAS POR 16 LINHAS

			A marca na posição será no valor correspondente do cruzamento da linha e coluna
			por exemplo :

			Se na coluna 5 linha 5 o valor for 1 então será criado um gerador de ITEM habilitado na posicao correnpondente

			Experimente trocando as posicoes das linhas abaixo colocando o programa para rodar
		 
			OBS: =1 CARREGADOR
				 =2 CARREGADOR DESABILITADO
				 =3 ALVO FALSO
				 =4 ALVO FALSO DESABILITADO
				 =5 ALVO
				 =6 ALVO DESABILITADO
			*/
			
			
			int qtdeJogadores;
			connClientWin->getPlayers(qtdeJogadores);
			int totLinha[PLAYERS_MAX];
			int totColuna[PLAYERS_MAX];
			int myPosAlvo;
			if(qtdeJogadores<1){return;}
			connClientWin->getAlvoPlayers(myPosAlvo, totLinha, totColuna);

			//Gerar alvos dos jogadores
			//posicao_tabuleiro[3+ rand () % 12][3+ rand () % 10]=3;
			for(int i=0; i<qtdeJogadores+PLAYERS_FALSO_MAX; i++){
				if(i<qtdeJogadores){
					posicao_tabuleiro[totColuna[i]][totLinha[i]] = ((i == myPosAlvo) ? 5 : 3);
				}else{
					//NPC
					posicao_tabuleiro[totColuna[i]][totLinha[i]] = 3;
				}
			}

			posicao_tabuleiro[3+ rand () % 12][15]=1;	//Carregador

			//int iniciando = 10;
			bool pressionadoESC = false;
		do
		{ //Inicio do jogo

			if(teclas[C2D2_ESC].pressionado){ perdeu=true;pressionadoESC=true;alvo_perdido=1;}

			xmouse = mouse->x;
			ymouse = mouse->y;

			// Limpa a tela com a cor de fundo atual
			C2D2_LimpaTela();

			C2D2_DesenhaSprite(level1background, 0, 0, 0);

			i = 1;// coluna
			j = 1;// linha
			for (i=1;i<24;i++){
				for (j=1;j<17;j++){
						if (posicao_tabuleiro[i][j]==1){//GERA CARREGADOR DA ARMA NA POSICOES INDICADAS
						temporizacarregador++;
						if (temporizacarregador == 5){
							quadroDefcarregador++;
							temporizacarregador=0;
						}
						if (quadroDefcarregador < 6 ){
							C2D2_DesenhaSprite(carregador, 0, i*32, j*32);
						}
						if (quadroDefcarregador > 4 ){
							C2D2_DesenhaSprite(carregador, 1, i*32, j*32);
						}
						if (quadroDefcarregador > 10 ){
							quadroDefcarregador = 0;
						}
					}	
					if (posicao_tabuleiro[i][j]==3){//GERA ALVO FALSO NAS POSICOES INDICADAS
						temporizacarregador++;
						if (temporizacarregador == 5){
							quadroDefcarregador++;
							temporizacarregador=0;
						}
						if (quadroDefcarregador < 6 ){
							C2D2_DesenhaSprite(alvo2, 0, i*32, j*32);
						}
						if (quadroDefcarregador > 4 ){
							C2D2_DesenhaSprite(alvo2, 1, i*32, j*32);
						}
						if (quadroDefcarregador > 10 ){
							quadroDefcarregador = 0;
						}
					}	
					if (posicao_tabuleiro[i][j]==5){// GERA ALVO
						temporizacarregador++;
						if (temporizacarregador == 5){
							quadroDefcarregador++;
							temporizacarregador=0;
						}
						if (quadroDefcarregador < 6 ){
							C2D2_DesenhaSprite(alvo1, 0, i*32, j*32);
						}
						if (quadroDefcarregador > 4 ){
							C2D2_DesenhaSprite(alvo1, 1, i*32, j*32);
						}
						if (quadroDefcarregador > 10 ){
							quadroDefcarregador = 0;
						}
					}
					if (posicao_tabuleiro[i][j]==2){// DESABILITA GERADORES DE ITEM
						temporizacarregador++;
						if (temporizacarregador == 5){
							quadroDefcarregador++;
							temporizacarregador=0;
						}
						if (quadroDefcarregador < 6 ){
							C2D2_DesenhaSprite(carregador, 2, i*32, j*32);
						}
						if (quadroDefcarregador > 4 ){
							C2D2_DesenhaSprite(carregador, 3, i*32, j*32);
						}
						if (quadroDefcarregador > 10 ){
							quadroDefcarregador = 0;
						}
					}
					if (posicao_tabuleiro[i][j]==7){// MARCADOR DE CARGA UTILIZADA
						C2D2_DesenhaSprite(ChanceUtilizada, quadroDefChanceUtilizada, i*32, j*32);
						//C2D2P_Circulo(i*32 + 14, j*32 + 14, 40, 255, 255, 255); // teste
					}
					if (xmouse > (i*32)-32 && xmouse < (i*32)+32 && ymouse > (j*32)-32 && ymouse < (j*32)+32){
						mouseposicaocol=i;
						mouseposicaolin=j;
				
					}
				}
			}

			if(mouse->botoes[C2D2_MESQUERDO].pressionado) // CARGA DE TIRO
			{
				if (posicao_tabuleiro[mouseposicaocol][mouseposicaolin]==1){ //MARCA CARREGADOR UTILIZADO
					posicao_tabuleiro[mouseposicaocol][mouseposicaolin]=7;
					tempoInicioSaque = clock();
					ArmaCarregada=1;
					i = 1;
					j = 1;
					for (i=1;i<24;i++){
						for (j=1;j<17;j++){
							if (posicao_tabuleiro[i][j]==1){
								posicao_tabuleiro[i][j]=2;
							}
						}
					}
				}
				if (posicao_tabuleiro[mouseposicaocol][mouseposicaolin]==3 && ArmaCarregada==1){ // SELECIONA ALVO FALSO
					i = 1;
					j = 1;
					for (i=1;i<24;i++){
						for (j=1;j<17;j++){
							//if (posicao_tabuleiro[i][j]==3){
								posicao_tabuleiro[i][j]=4;
								alvo_perdido = 1;
							//}
						}
					}
				}
				if (posicao_tabuleiro[mouseposicaocol][mouseposicaolin]==5 && ArmaCarregada==1){ // ACERTA ALVO
					i = 1;
					j = 1;
					for (i=1;i<24;i++){
						for (j=1;j<17;j++){
							//if (posicao_tabuleiro[i][j]==5){
								posicao_tabuleiro[i][j]=6;
								alvo_destruido = 1;
							//}
						}
					}
				}
			}
		
			//if (ArmaCarregada==1){ // unidades de Carga habilitada a (CARGA GASTA 1), alvos falsos(CUSTO 1) e chance extra(GANHA 1)
				i = 1;
				j = 1;
				for (i=1;i<24;i++){
					for (j=1;j<17;j++){
						if (posicao_tabuleiro[i][j]==2){
							posicao_tabuleiro[i][j]=1;
						}
						if (posicao_tabuleiro[i][j]==4){
							posicao_tabuleiro[i][j]=3;
						}
						if (posicao_tabuleiro[i][j]==6){
							posicao_tabuleiro[i][j]=5;
						}
					}
				}
			//}

			// Desenha quantidade de Chances do jogador
			C2D2_DesenhaTexto(fonte32, 580, 15, player.getLogin().c_str(), C2D2_TEXTO_ESQUERDA);

			// Desenha Pontos do jogador
			char strCredito[10];
			sprintf(strCredito, "$ %d", player.getCredito());
			C2D2_DesenhaTexto(fonte32, 580, 45, strCredito, C2D2_TEXTO_ESQUERDA);

			// Desenha quantidade de Chances do jogador
			char strChances[255];
			sprintf(strChances, "Chances: %d", Chances);
			C2D2_DesenhaTexto(fonte32, 580, 100, strChances, C2D2_TEXTO_ESQUERDA);

			// Desenha quantidade de ALVOS atingidos
			char strAlvosAcertos[100];
			sprintf(strAlvosAcertos, "Acertos: %d", AlvosAcertos);
			C2D2_DesenhaTexto(fonte32, 580, 130, strAlvosAcertos, C2D2_TEXTO_ESQUERDA);

			C2D2_DesenhaSprite(carregador, 0, 580, 190);
			C2D2_DesenhaSprite(alvo1, 0, 580, 230);
			C2D2_DesenhaSprite(alvo2, 0, 580, 270);

			C2D2_DesenhaTexto(fonte32, 610, 190, "Carregador", C2D2_TEXTO_ESQUERDA);
			C2D2_DesenhaTexto(fonte32, 610, 230, "Alvo", C2D2_TEXTO_ESQUERDA);
			C2D2_DesenhaTexto(fonte32, 610, 270, "Alvo Falso", C2D2_TEXTO_ESQUERDA);

			char strPlayers[50];
			sprintf(strPlayers, "Players: %d", qtdeJogadores);
			C2D2_DesenhaTexto(fonte32, 580, 350, strPlayers, C2D2_TEXTO_ESQUERDA);

			/*char strTempoLimite[1];
			sprintf(strTempoLimite, "Tempo: %d", ctime(&now));
			C2D2_DesenhaTexto(fonte32, 580, 350, strTempoLimite, C2D2_TEXTO_ESQUERDA);*/
			

			// Escreve instruções para sair do gameplay
			C2D2_DesenhaTexto(fonte32, 600, 445, "ESC = Sair", C2D2_TEXTO_ESQUERDA);

			// Gera mouse
			C2D2_DesenhaSprite(ponteiroMouse, 0, xmouse, ymouse);

			// Lógica animação do mouse
			if(mouse->botoes[C2D2_MESQUERDO].pressionado)
			{
				if (ArmaCarregada == 1)
				{
					C2D2_DesenhaSprite(ponteiroMouse, 1, xmouse, ymouse);
					indice_tiro = rand () % 6;
					CA2_TocaEfeitoTela(Tiro[indice_tiro], 1);
				}
				else
				{
					CA2_TocaEfeitoTela(SemTiro, 1);
				}
			}

			// Faz a lógica da animação do ALVO
			if(--tempoQuadroIni == 0)
			{
				quadroAtualIni = (quadroAtualIni+1)%4;
				tempoQuadroIni = 10;
			}


			// ACABA O TEMPO DO ALVO ATIVO
			if(alvo_perdido==1) {
				gameAlvoPlayer.acertou = false;
				gameAlvoPlayer.coluna = mouseposicaocol;
				gameAlvoPlayer.linha = mouseposicaolin;
				gameAlvoPlayer.tempo = 0;
				connClientWin->sendAlvo(gameAlvoPlayer);

				// JOGADOR PERDE UMA CHANCE
				CA2_TocaEfeito(PerdidoAlvo, 300);
				--Chances;
				C2D2_DesenhaTexto(fonte32, 300, 300, "ALVO PERDIDO!", C2D2_TEXTO_CENTRALIZADO);
		
				//C2D2_Pausa(5000); // TROCAR POR AGUARDAR NOVA CONEXAO
				int resp = connClientWin->receiveAlvo(gameAlvoPlayerResponse);
				if(resp == SOCKET_ERROR){return;}
				char auxBuf[255];
				sprintf(auxBuf, "Mais rapido: %s", gameAlvoPlayerResponse.login);
				C2D2_DesenhaTexto(fonte32, 300, 350, auxBuf, C2D2_TEXTO_CENTRALIZADO);
				if(myPosAlvo == gameAlvoPlayerResponse.posAlvo){
					//AlvosAcertos +=1;
				}
			}

			// SE O ALVO FOR ATINGIDO
			if(alvo_destruido==1) {
				gameAlvoPlayer.acertou = true;
				gameAlvoPlayer.coluna = mouseposicaocol;
				gameAlvoPlayer.linha = mouseposicaolin;
				gameAlvoPlayer.tempo = (clock() - tempoInicioSaque);
				connClientWin->sendAlvo(gameAlvoPlayer);
				player.setCredito(player.getCredito()+10);

				CA2_TocaEfeito(DestruidoAlvo, 300);
				--Chances;
				C2D2_DesenhaTexto(fonte32, 300, 300, "ALVO DESTRUIDO!", C2D2_TEXTO_CENTRALIZADO);
				
				//C2D2_Pausa(5000); // TROCAR POR AGUARDAR NOVA CONEXAO
				//Resposta de quem acertou
				int resp = connClientWin->receiveAlvo(gameAlvoPlayerResponse);
				if(resp == SOCKET_ERROR){return;}
				char auxBuf[255];
				sprintf(auxBuf, "+ Rapido: %s", gameAlvoPlayerResponse.login);
				C2D2_DesenhaTexto(fonte32, 300, 350, auxBuf, C2D2_TEXTO_CENTRALIZADO);

				char auxBuf2[255];
				sprintf(auxBuf2, "(Meu tempo %d)", gameAlvoPlayer.tempo);
				C2D2_DesenhaTexto(fonte32, 300, 380, auxBuf2, C2D2_TEXTO_CENTRALIZADO);
				if(myPosAlvo == gameAlvoPlayerResponse.posAlvo){
					AlvosAcertos +=1;
				}

			}

			// Troca os buffers de imagem e esperar o tempo para 60fps
			C2D2_Sincroniza(C2D2_FPS_PADRAO);

		}while(alvo_perdido + alvo_destruido == 0);

		if((Chances <= 0) || pressionadoESC)
		{
			perdeu = true;
			if(perdeu == true)
			{
			C2D2_DesenhaTexto(fonte32, 300, 200, "GAME OVER!", C2D2_TEXTO_CENTRALIZADO);
			C2D2_Sincroniza(C2D2_FPS_PADRAO);
			C2D2_Pausa(5000);
			}
		}
	}while(perdeu == false);

	//Disconnect
	connClientWin->restart();
	servidorDisponivel = false;

	C2D2_RemoveSpriteSet(carregador);
	C2D2_RemoveSpriteSet(alvo1);
	C2D2_RemoveSpriteSet(alvo1Acerto);
	C2D2_RemoveSpriteSet(alvo2);
	C2D2_RemoveSpriteSet(alvo2Acerto);
	C2D2_RemoveSpriteSet(ChanceUtilizada);
	C2D2_RemoveSpriteSet(ponteiroMouse);
	
	CA2_RemoveEfeito(ChanceUtilizadaAtaque);
	CA2_RemoveEfeito(DestruidoAlvo);
	CA2_RemoveEfeito(PerdidoAlvo);
	CA2_RemoveEfeito(SemTiro);
	
	for(int i=0; i< (sizeof(Tiro)/sizeof(*Tiro)); ++i){
		CA2_RemoveEfeito(Tiro[i]);
	}

	//encerra a musica
	//CA2_RemoveMusica(musica_fundo);

	//C2D2_LimpaTela();
	estadoatual = 1;
}

void Menu::telaRanking()
{
	//Lista players
	std::vector<Player> players;

	// Recupera o teclado
	C2D2_Botao *teclas = C2D2_PegaTeclas();
    C2D2_Mouse *mouse = C2D2_PegaMouse();

    // Variável para o botão, 1 se o mouse está em cima, 0 caso contrário
    int bspr_btn_voltar=0, bspr_btn_atualizar=0;

	if(!servidorDisponivel){
		servidorDisponivel = !connClientWin->restart();
	}else{
		connClientWin->getRanking(players);
	}

    // Troca a cor de limpeza
    C2D2_TrocaCorLimpezaTela(0, 0, 0);
	do
	{
        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            estadoatual=1;
        
		bspr_btn_voltar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_voltar, 0, 10,470)) ? 1 : 0 ;
		bspr_btn_atualizar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_atualizar, 0, LARGURA_TELA-100-10,470)) ? 1 : 0 ;
		
		
        // Se o botão do mouse está pressionado, toma uma ação
		if(mouse->botoes[C2D2_MESQUERDO].pressionado) {
			if(bspr_btn_voltar==1){
					connClientWin->restart();
					connClientWin->tryAccept();
					estadoatual=1; //MenuPrincipal
			}else if(bspr_btn_atualizar==1){
				connClientWin->restart();
				servidorDisponivel = connClientWin->tryAccept();
				
				if(servidorDisponivel){
					//Busca Creditos
					players.clear();
					connClientWin->getRanking(players);
				}
			}
		}

        // Limpa a tela e desenha
		C2D2_LimpaTela();
		
		//Titulo
		C2D2_DesenhaSprite(spr_titulo_ranking, 0, 0, 0);
		//C2D2_DesenhaTexto(fonte32, 10, 20, "Ranking TiroCerto:", C2D2_TEXTO_ESQUERDA);
		int spacer = 85;
		if(!servidorDisponivel){
			C2D2_DesenhaTexto(fonte32, 60, spacer, "Servidor offline", C2D2_TEXTO_ESQUERDA);
		}else{
			char buffer[255];
			for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it){
				sprintf_s(buffer, "$ %000d  ::  %s", it->getCredito(), it->getLogin().c_str() );
				C2D2_DesenhaTexto(fonte32, 60, spacer, buffer, C2D2_TEXTO_ESQUERDA);
				spacer += 30;
			}
		}

		C2D2_DesenhaSprite(spr_btn_voltar, bspr_btn_voltar, 10, 470);
		C2D2_DesenhaSprite(spr_btn_atualizar, bspr_btn_atualizar, LARGURA_TELA-100-10, 90);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);

		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}while(estadoatual==6);
	//servidorDisponivel = connClientWin->tryAccept();
}

void Menu::telaCreditos()
{
	// Recupera o teclado
	C2D2_Botao *teclas = C2D2_PegaTeclas();
    C2D2_Mouse *mouse = C2D2_PegaMouse();

    // Variável para o botão, 1 se o mouse está em cima, 0 caso contrário
    int bspr_btn_voltar=0;

    // Troca a cor de limpeza para verde
    C2D2_TrocaCorLimpezaTela(0, 0, 0);
	do
	{
        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            estadoatual=4;
        
		bspr_btn_voltar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_voltar, 0, 10,470)) ? 1 : 0 ;

        // Se o botão do mouse está pressionado, toma uma ação
		if(mouse->botoes[C2D2_MESQUERDO].pressionado) {
			if(bspr_btn_voltar==1){
				estadoatual=1; //MenuPrincipal 1
			}
		}

        // Limpa a tela e desenha
		C2D2_LimpaTela();

		//C2D2_DesenhaTexto(fonte32, 10, 20, "Desenvolvedores:", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaSprite(spr_titulo_sobre, 0, 0, 0);
		C2D2_DesenhaTexto(fonte32, 30, 80, "Daniel Elias de Liz", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(fonte32, 30, 130, "Enzo Marchiorato", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaTexto(fonte32, 30, 180, "Oscar Leal", C2D2_TEXTO_ESQUERDA);

		C2D2_DesenhaTexto(fonte32, 10, 440, "2014 PUCPR - Multiplayer (Johnny)", C2D2_TEXTO_ESQUERDA);

		C2D2_DesenhaSprite(spr_btn_voltar, bspr_btn_voltar, 10, 470);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);

		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	
	}while(estadoatual==4);
}


/** 3 - NovoUsuario*/
void Menu::telaNovoUsuario(){
	C2D2_Botao *teclas = C2D2_PegaTeclas();
    C2D2_Mouse *mouse = C2D2_PegaMouse();
	static Evento evCursor;
	std::string msgValidacao("Click em OK");

	ebUsuario = Editbox21(377, 120, LARGURA_TELA-10,180, false)
									.setCorNormal(255,255,255)
									.setCorColisao(0,255,0)
									.setCorEdicao(0,255,255)
									.setFonte(fonte32);
	ebSenha = Editbox21(314, 210, LARGURA_TELA-10,270, true)
								.setCorNormal(255,255,255)
								.setCorColisao(0,255,0)
								.setCorEdicao(0,255,255)
								.setFonte(fonte32);
	/*ebEmail = Editbox21(314, 300, LARGURA_TELA-10,360, false)
								.setCorNormal(255,255,255)
								.setCorColisao(0,255,0)
								.setCorEdicao(0,255,255)
								.setFonte(fonte32);*/


    // Variáveis para os botões, 1 se o mouse está em cima, 0 caso contrário
    int bspr_btn_voltar=0, bspr_btn_ok=0;
	int bspr_txt_usuario=0, bspr_txt_senha=0, bspr_txt_email=0;
	int bebUsuario, bebSenha, bebEmail;

    // Sincroniza para atualizar o teclado
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	do {

		//TODO Mudar para o loading EVT_LOADING_GAME_REDE_START
		if(teclas[C2D2_CIMA].pressionado)	{
			evCursor.tipoEvento = EVT_PRESSIONOU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}
		//EVT_LOADING_GAME_REDE_END
		if(teclas[C2D2_CIMA].liberado)	{
			evCursor.tipoEvento = EVT_LIBEROU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}

        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            encerra=true;
        //Estado sobre os btn
		bspr_btn_voltar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_voltar, 0, 10,470)) ? 1 : 0 ;
		bspr_btn_ok = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_ok, 0, LARGURA_TELA-100-10,470)) ? 1 : 0 ;

		//Estado sobre os EDT
        bebUsuario = ebUsuario.colidiu(mouse->x, mouse->y, 10,10) ? 1 : 0 ;
		ebUsuario.setTipoEstado(bebUsuario);
		bebSenha = ebSenha.colidiu(mouse->x, mouse->y, 10,10) ? 1 : 0 ;
		ebSenha.setTipoEstado(bebSenha);

        // Se o botão do mouse está pressionado, toma uma ação
        if(mouse->botoes[C2D2_MESQUERDO].pressionado) {
            // O botão ativo é o botão da ação equivalente
            if(bspr_btn_voltar==1){
				estadoatual=1; //MenuPrincipal
			}else if(bspr_btn_ok==1){
				if(!servidorDisponivel){ servidorDisponivel = connClientWin->tryAccept(); }
				
				if(servidorDisponivel){
					player.setLogin( ebUsuario.getTexto() );
					player.setSenha( ebSenha.getTexto() );
					int codMsg = connClientWin->novoPlayer( player );
					if(codMsg == AUTH_MSG_CADASTRO_OK){
						msgValidacao = "Aguardando para iniciar";
						estadoatual=5; //Jogo
						
					}else if(codMsg == AUTH_MSG_EMANDAMENTO){
						msgValidacao = "Jogo em andamento, aguarde nova partida";
						servidorDisponivel = !connClientWin->restart();
					}else{
						msgValidacao = "Usuario ou senha invalidos/existente";
						servidorDisponivel = !connClientWin->restart();
					}
				}else{
					msgValidacao = "Servidor offline, tente mais tarde!";
				}

			}else if(bebUsuario==1){
				ebUsuario.setTipoEstado(EB21_TE_EDICAO);
			}else if(bebSenha==1){
				ebSenha.setTipoEstado(EB21_TE_EDICAO);
			}
        }

        // Limpa a tela e desenha
		ATOR_Atualiza(aCursor, 0);
		C2D2_LimpaTela();
		ebUsuario.atualiza();
		ebSenha.atualiza();
		ATOR_AplicaEstado(aCursor, 0, 0, 0);

		//Titulo
		C2D2_DesenhaSprite(spr_titulo_novousuario, 0, 0, 0);

		// Desenha os botões de acordo com o estado
		C2D2_DesenhaSprite(spr_txt_usuario, 0, 10, 115);
		ebUsuario.desenha();

		C2D2_DesenhaSprite(spr_txt_senha, 0, 10, 205);
		ebSenha.desenha();

		//Validacao
		if(ebUsuario.isTextoEmpty()){
			msgValidacao = "Digite o nome de Usuário";
		}else if(ebSenha.isTextoEmpty()){
			msgValidacao = "Digite uma Senha (apenas letras)";
		}//else if(ebEmail.isTextoEmail()){
			//msgValidacao = "Digite um Email (1=. e 2=@)";
		//}
		C2D2_DesenhaTexto(fonte32, (LARGURA_TELA/2), 400, msgValidacao.c_str(), C2D2_TEXTO_CENTRALIZADO);


		C2D2_DesenhaSprite(spr_btn_voltar, bspr_btn_voltar, 10, 470);
		C2D2_DesenhaSprite(spr_btn_ok, bspr_btn_ok, LARGURA_TELA-100-10, 470);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);

		ATOR_Desenha(aCursor, 0, mouse->x, mouse->y);

		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	while(!encerra && estadoatual==3);
}

/** 2 - Login*/
void Menu::telaLogin() {
	C2D2_Botao *teclas = C2D2_PegaTeclas();
    C2D2_Mouse *mouse = C2D2_PegaMouse();
	static Evento evCursor;

	ebUsuario = Editbox21(377, 140, LARGURA_TELA-10,210, false)
									.setCorNormal(255,255,255)
									.setCorColisao(0,255,0)
									.setCorEdicao(0,255,255)
									.setFonte(fonte32);
	ebSenha = Editbox21(314, 230, LARGURA_TELA-10,300, true)
								.setCorNormal(255,255,255)
								.setCorColisao(0,255,0)
								.setCorEdicao(0,255,255)
								.setFonte(fonte32);


    // Variáveis para os botões, 1 se o mouse está em cima, 0 caso contrário
    int bspr_btn_voltar=0, bspr_btn_ok=0;
	int bspr_txt_usuario=0, bspr_txt_senha=0;
	int bebUsuario, bebSenha;
	std::string msgValidacao;

    // Sincroniza para atualizar o teclado
	C2D2_Sincroniza(C2D2_FPS_PADRAO);
	do {

		//TODO Mudar para o loading EVT_LOADING_GAME_REDE_START
		if(teclas[C2D2_CIMA].pressionado)	{
			evCursor.tipoEvento = EVT_PRESSIONOU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}
		//EVT_LOADING_GAME_REDE_END
		if(teclas[C2D2_CIMA].liberado)	{
			evCursor.tipoEvento = EVT_LIBEROU_CIMA;
			ATOR_EnviaEvento(aCursor, &evCursor);
		}

        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            encerra=true;
        //Estado sobre os btn
		bspr_btn_voltar = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_voltar, 0, 10,470)) ? 1 : 0 ;
		bspr_btn_ok = (C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, spr_btn_ok, 0, LARGURA_TELA-100-10,470)) ? 1 : 0 ;

		//Estado sobre os EDT
        bebUsuario = ebUsuario.colidiu(mouse->x, mouse->y, 10,10) ? 1 : 0 ;
		ebUsuario.setTipoEstado(bebUsuario);
		bebSenha = ebSenha.colidiu(mouse->x, mouse->y, 10,10) ? 1 : 0 ;
		ebSenha.setTipoEstado(bebSenha);

        // Se o botão do mouse está pressionado, toma uma ação
        if(mouse->botoes[C2D2_MESQUERDO].pressionado) {
            // O botão ativo é o botão da ação equivalente
            if(bspr_btn_voltar==1){
				estadoatual=1; //MenuPrincipal
			}else if(bspr_btn_ok==1){
				if(!servidorDisponivel){ servidorDisponivel = connClientWin->tryAccept(); }
				
				if(servidorDisponivel){
					player.setLogin( ebUsuario.getTexto() );
					player.setSenha( ebSenha.getTexto() );
					int codMsg = connClientWin->autenticaPlayer( player );
					if(codMsg == AUTH_MSG_VERIFICAUSER_ERROR){
						msgValidacao = "Usuario ou senha invalidos";
						servidorDisponivel = !connClientWin->restart();
						
					}else if(codMsg == AUTH_MSG_EMANDAMENTO){
						msgValidacao = "Jogo em andamento, aguarde nova partida";
						servidorDisponivel = !connClientWin->restart();
					}else{
						msgValidacao = "Aguardando para iniciar";
						estadoatual=5; //Jogo
					}
				}else{
					msgValidacao = "Servidor offline, tente mais tarde!";
				}

                //
			}else if(bebUsuario==1){
				ebUsuario.setTipoEstado(EB21_TE_EDICAO);
			}else if(bebSenha==1){
				ebSenha.setTipoEstado(EB21_TE_EDICAO);
			}
        }

        // Limpa a tela e desenha
		ATOR_Atualiza(aCursor, 0);
		C2D2_LimpaTela();
		ebUsuario.atualiza();
		ebSenha.atualiza();
		ATOR_AplicaEstado(aCursor, 0, 0, 0);

		//Titulo
		C2D2_DesenhaSprite(spr_titulo_login, 0, 0, 0);

		// Desenha os botões de acordo com o estado
		C2D2_DesenhaSprite(spr_txt_usuario, 0, 10, 140);
		ebUsuario.desenha();

		C2D2_DesenhaSprite(spr_txt_senha, 0, 10, 230);
		ebSenha.desenha();
		//C2D2P_Retangulo(314, 230, LARGURA_TELA-10,300, 255,255,255);

		//Validacao
		if(ebUsuario.isTextoEmpty()){
			msgValidacao = "Digite o nome de Usuário";
		}else if(ebSenha.isTextoEmpty()){
			msgValidacao = "Digite uma Senha (apenas letras)";
		}
		//Msg erro de conexao
		C2D2_DesenhaTexto(fonte32, (LARGURA_TELA/2), 345, msgValidacao.c_str(), C2D2_TEXTO_CENTRALIZADO);

		C2D2_DesenhaSprite(spr_btn_voltar, bspr_btn_voltar, 10, 470);
		C2D2_DesenhaSprite(spr_btn_ok, bspr_btn_ok, LARGURA_TELA-100-10, 470);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);

		ATOR_Desenha(aCursor, 0, mouse->x, mouse->y);

		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	while(!encerra && estadoatual==2);


	/*do
	{
        // Lógica: se pressiona ESC no menu, deve sair fora
        if(teclas[C2D2_ESC].pressionado)
            estadoatual=1;
        // Vê se o mouse está em cima de um botão e atualiza o estado
        if(C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, botao_voltar, 0, 550, 480))
            bvoltar=1;
        else
            bvoltar=0;

		if(C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, selecao_fundo_item, 0, 20, 120)){
            bSelecaoJogo1=1;
			fase_selecionada=0;
		}else{
            bSelecaoJogo1=0;
		}

		if(C2D2_ColidiuSprites(spmira, 0, mouse->x, mouse->y, selecao_fundo_item, 0, 200, 120)){
            bSelecaoJogo2=1;
			fase_selecionada=1;
		}else{
            bSelecaoJogo2=0;
		}

        // Se o botão do mouse está pressionado, toma uma ação
        if(mouse->botoes[C2D2_MESQUERDO].pressionado)
        {
			if(bSelecaoJogo1==1){
				fase_selecionada=0;
				estadoatual=4;
			}else if(bSelecaoJogo2==1){
				fase_selecionada=1;
				estadoatual=4;
			}

            // O botão ativo é o botão da ação equivalente
            if(bvoltar==1)
                estadoatual=1;

        }

        // Limpa a tela e desenha
		C2D2_LimpaTela();

		C2D2_DesenhaTexto(fonte32, 400, 30, "Selecione a fase", C2D2_TEXTO_CENTRALIZADO);

        // Desenha o botão de acordo com o estado
		C2D2_DesenhaSprite(selecao_fundo_item, bSelecaoJogo1, 20, 120);
		C2D2_DesenhaSprite(selecao_fundo_item, bSelecaoJogo2, 200, 120);

		//Apos leitura do arquivo, setar aqui o score por fase
		//C2D2_DesenhaSprite(selecao_item_ranking, 0, 25, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 2, 65, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 5, 105, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 6, 26, 160);
		C2D2_DesenhaTexto(fonte32, 60, 160, "6", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaSprite(selecao_item_ranking, 7, 26, 190);
		C2D2_DesenhaTexto(fonte32, 60, 190, "1:30", C2D2_TEXTO_ESQUERDA);
		//fase2
		C2D2_DesenhaSprite(selecao_item_ranking, 2, 205, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 5, 245, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 5, 285, 125);
		C2D2_DesenhaSprite(selecao_item_ranking, 6, 206, 160);
		C2D2_DesenhaTexto(fonte32, 240, 160, "2", C2D2_TEXTO_ESQUERDA);
		C2D2_DesenhaSprite(selecao_item_ranking, 7, 206, 190);
		C2D2_DesenhaTexto(fonte32, 240, 190, "0:17", C2D2_TEXTO_ESQUERDA);

		C2D2_DesenhaSprite(botao_voltar, bvoltar, 550,480);

        //Desenha a mira
        C2D2_DesenhaSprite(spmira, 0, mouse->x, mouse->y);
		// Faz a troca do front buffer com o back buffer e atualiza as entradas
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	while(estadoatual==2);
	*/
}
