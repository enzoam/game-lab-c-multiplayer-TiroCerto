#include <stdio.h>
#include <stdlib.h>

#include "Menu.h"
//int main_teste(int narg, char **valarg)

int main(int argc, char **argv) {
	Menu* menu = new Menu();
	menu->start();

	getchar();
	return 0;
}