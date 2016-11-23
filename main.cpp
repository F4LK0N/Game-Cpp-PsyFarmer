//GLOBAL VARS
int tileSize=64;

int **mapTiles;
int mapRows=0;
int mapCols=0;

#pragma once
#include "Jogo.h"



int main(int argc, char* argv[]){
	Jogo jogo;
	jogo.inicializar();
	jogo.executar();
	jogo.finalizar();
	return 0;
}