#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"

#include "Modal.h"



class MapList
{
	public:
		MapList();
		~MapList();

		bool load(string path, Modal &modal);
		void allocate(int size);
		void add(string map);
		bool next();
		string get();

	private:
		string *list;
		int pointer;
		int size;
};



