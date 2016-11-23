#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"

#include "Item.h"



class Player
{
	public:
		Player();
		~Player();

		void load(string spritesheetName, string imagePath, int animations, int frames, int x, int y);
		void unload();

		int getX();
		int getY();
		
		void draw(int canvasStartX, int canvasStartY);
		void animate();
		void control(Item *itens, int itensQt);
		void move(int dirX, int dirY);

		void die();
		bool isInvulnerable();

		int getScore();
		int getLifes();

		void reset();

	private:
		string spritesheetName;
		string imagePath;
		int animations;
		int frames;
		int x, startX;
		int y, startY;
		bool moving;
		int drawX;
		int drawY;
		Sprite spritesheet;
		int score;
		int lifes;
		int invulnerable;
};




