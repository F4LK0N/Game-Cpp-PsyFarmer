#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"



class Item
{
	public:
		Item();
		~Item();

		void load(int type, int x, int y);
		void draw(int canvasStartX, int canvasStartY);
		bool move(int dirX, int dirY);
		void fall();

		int getX();
		int getY();

		bool isActive();
		
	private:
		bool status;
		int type;
		int x;
		int y;
		bool moving;
		bool falling;
		int fallingDelay;
		int drawX;
		int drawY;
		Sprite spritesheet;
};

