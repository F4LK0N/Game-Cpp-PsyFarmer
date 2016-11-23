#pragma once
#include <string>
using namespace std;
#include "Player.h"
#include "Enemy.h"

enum fileSource {INTERNAL,DLC};

class FileView
{
	public:
		FileView();
		~FileView();
		string load(string path, int source);
		bool run();

	private:
		Player *players;
		Enemy *enemies;
		bool loadStatus;

};

