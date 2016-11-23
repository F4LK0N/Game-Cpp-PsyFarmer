#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"



class MenuItem
{
	public:
		MenuItem();
		~MenuItem();

		void inicializar(string texto, int x, int y);
		void setString(string texto);
		int getX();
		int getLargura();

		void draw();

		bool mouseOver();

	private:
		Texto texto;

		int x;
		int y;
		int largura;
		int altura;

		int paddingLeft  =12;
		int paddingRight =15;
		int paddingTop   =7;
		int paddingBottom=5;
};

