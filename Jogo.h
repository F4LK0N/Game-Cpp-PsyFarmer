#pragma once
#include <string>
#include <time.h>
using namespace std;
#include "libUnicornio.h"

enum runningInstance {rExit,rModal,rMenu,rGame};
enum menu {mPause,mMain,mDLC,mRules,mCredits,mGameOver,mGameEnd,mLevelEnd};

//FUNCTIONS
#include "ParametersManager.h"

//CLASSES
#include "Modal.h"
#include "Menu.h"

#include "InterfaceFkn.h"

#include "MapList.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "TileFkn.h"
#include "Item.h"



class Jogo
{
	public:
		Jogo();
		~Jogo();

		void inicializar();
		void finalizar();

		void executar();

	private:
		//INSTANCES
		int running;
		int runningLast;
		int runningMenu;

		//MODAL
		Modal modal;
		
		//MENUS
		Menu menu[8];
		void menuMain();
		void menuPause();
		void menuGameOver();
		void menuGameEnd();
		void menuLevelEnd();
		void menuCredits();
		Texto menuText;
		int menuWait;

		//INTERFACE
		InterfaceFkn interfaceFkn;

		//MAPLIST
		MapList mapList;

		//MAP
		Map map;

		//GAME
		bool runGame();
		
		//PLAYER
		Player *player;//TROCAR PARA NÃO PONTEIRO
};




