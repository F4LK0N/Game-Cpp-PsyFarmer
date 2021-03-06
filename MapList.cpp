#include "MapList.h"


//#####################################################################################################################################################################
MapList::MapList(){
	pointer=0;
	size=0;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
MapList::~MapList(){
	delete[] list;   }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool MapList::load(string path, Modal &modal)
{
	pointer=0;
	
	//LOAD FILE
	ifstream file;
	file.open(path);

	//FILE NOT FOUND
	if(!file.is_open()){
		modal.setMsg("Arquivo n�o encontrado!");
		return false; }

	//COUNT LINES
	int lines=0;
	while(!file.eof()){
		string temp;
		getline(file, temp);
		if(temp!=""){ lines++; }
	}
	file.clear();
	file.seekg(0);

	//NO MAPS
	if(lines<1){
		file.close();
		modal.setMsg("Nenhum mapa encontrado!");
		return false;
	}

	//MOUNT MAPLIST
	allocate(lines);
	while(!file.eof()){
		string temp;
		getline(file, temp);
		if(temp!=""){ add(temp); }
	}

	//SUCCESS
	file.close();
	return true;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void MapList::allocate(int size){
	this->size=size;
	list=new string[size];
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void MapList::add(string map){
	for(int i=0; i<size; i++){
		if(list[i]==""){
			list[i]=map;
			break;
		}
	}
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool MapList::next()
{
	if(pointer==size-1){
		return false; }

	pointer++;
	return true;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
string MapList::get(){
	return list[pointer]; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################