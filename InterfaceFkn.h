#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"

#include "Player.h"



class InterfaceFkn
{
	public:
		InterfaceFkn();
		~InterfaceFkn();

		void init();
		void draw(Player *player);

	private:
		Sprite life;
		Texto score;
};

