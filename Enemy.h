#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"



class Enemy
{
	public:
		Enemy();
		~Enemy();

		void load(string spritesheetName, string imagePath, int animations, int frames, int x, int y);
		void unload();
		
		bool move(int dirX, int dirY);
		void control();
		void draw(int canvasStartX, int canvasStartY);
		
		void die();
		
		int getX();
		int getY();

		bool isActive();


	private:
		bool status;
		int type;//1|2

		string spritesheetName;
		string imagePath;
		int animations;
		int frames;

		int x;
		int y;

		int moveDelay;

		bool moving;
		int drawX;
		int drawY;

		Sprite spritesheet;
};

