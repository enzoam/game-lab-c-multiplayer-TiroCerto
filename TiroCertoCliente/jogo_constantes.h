#ifndef JOGO_CONSTANTES_H
#define JOGO_CONSTANTES_H

// As dimensões da tela desejada (cheia)
#define RELOGIODIGITAL_X	692
#define RELOGIODIGITAL_Y	5
#define RELOGIODIGITAL_S	116000

#define SCOREFILE	"TiroCerto.savegame"

#define LARGURA_TELA	800
#define ALTURA_TELA		600
#define GAMENOMEVERSAO	"TiroCerto v1.00"

#if	defined(linux)
    #define IMAGES_DIR "images/"
#else
    #define IMAGES_DIR "./images/"
#endif

#endif
