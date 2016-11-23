#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"

#include "ParametersManager.h"

#include "Modal.h"

#include "Player.h"
#include "Enemy.h"
#include "TileFkn.h"
#include "Item.h"

class Map
{
	public:
		Map();
		~Map();
		
		bool load(string path, Modal &modal);
		void unload();

		void setPlayer(Player *player);//?????

		int getRows();
		int getCols();

		bool run();
		void draw();

	private:
		//PLAYER
		Player *player; //somente um, ao invez de ter dois.
		Player *players;
		int playerQt;
		//ENEMY
		Enemy *enemies;
		int enemyQt;
		//ITENS
		Item *itens;
		int itensQt;
		//TILE
		TileFkn *tiles;
		int tileQt;
		TileFkn *tilesExtra;
		
		//CANVAS
		int drawStartX;//RENAME canvasStartX
		int drawStartY;//RENAME canvasStartY
};




