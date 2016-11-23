#pragma once
#include <string>
using namespace std;
#include "libUnicornio.h"

class Modal
{
	public:
		Modal();
		~Modal();
		void setMsg(string message);
		string getMsg();
		bool run();
	private:
		Texto message;
		string messageBKP;
		Texto buttonText;

};

