#include "ParametersManager.h"

//#####################################################################################################################################################################
int paramsCount(string line){
	int params=0;

	bool searchingParam=true;
	bool isParam=false;
	int lineSize=line.size();
	for(int i=0; i<lineSize; i++){
		//IS PARAM?
		if(line[i]!=32 && line[i]!=9){ isParam=true; }else{ isParam=false; }

		//PARAM
		if(searchingParam && isParam){
			searchingParam=false;
			params++; }

		//SPACES
		else if(!searchingParam && !isParam){
			searchingParam=true; }
	}

	return params;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
string paramGet(string line, int paramNum){
	int params=0;
	string param="";

	bool searchingParam=true;
	bool isParam=false;
	int lineSize=line.size();
	for(int i=0; i<lineSize; i++){
		//IS PARAM?
		if(line[i]!=32 && line[i]!=9){ isParam=true; }else{ isParam=false; }

		//IS PARAM
		if(searchingParam && isParam){
			searchingParam=false;
			params++; }

		//IS SPACE
		else if(!searchingParam && !isParam){
			searchingParam=true; }

		//PARAM
		if(isParam && params==paramNum){
			param+=line[i];
		}
	}

	return param;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################




