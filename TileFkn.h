#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"



class TileFkn
{
	public:
		TileFkn();
		~TileFkn();
		
		void load(string spritesheetName, string imagePath, int animations, int frames);
		void unload();

		void draw(int x, int y);
		void animate();

	private:
		string spritesheetName;
		string imagePath;
		int animations;
		int frames;

		Sprite spritesheet;
};




