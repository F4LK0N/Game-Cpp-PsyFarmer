#include "FileView.h"
#include <fstream>



FileView::FileView()
{
}


FileView::~FileView()
{
}
 
string FileView::load(string path, int source=DLC)
{
	ifstream gameFile;

	//PATH
	if(source==INTERNAL){
		path="_internal/"+path; }
	else{
		path="dlcs/"+path; }

	//OPEN
	gameFile.open(path);
	if(!gameFile.is_open()){
		return "N�o foi poss�vel localizar o arquivo!"; }

	



	//SUCCESS
	return "1";
	
	
	//FAIL
	return "Erro inesperado!";
}

bool FileView::run()
{
	return false;
}
