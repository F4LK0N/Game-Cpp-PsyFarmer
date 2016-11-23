#include "Map.h"


//#####################################################################################################################################################################
Map::Map(){
	playerQt=0;
	enemyQt=0;
	tileQt=0;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
Map::~Map(){}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool Map::load(string path, Modal &modal){
	
	//#################################################################################################################
	// LOAD FILE
	//#################################################################################################################
	//LOAD FILE
	ifstream file;
	file.open(path+".map");

	//FILE NOT FOUND
	if(!file.is_open()){
		modal.setMsg("Arquivo não encontrado!");
		return false; }

	//COUNT LINES
	int lines=0;
	while(!file.eof()){
		string temp;
		getline(file, temp);
		lines++;
	}
	file.clear();
	file.seekg(0);
	
	//CHECK SIZE
	if(lines<8){
		modal.setMsg("Estrutura do arquivo invalida!");
		return false; }
	//#################################################################################################################
	//#################################################################################################################
	//#################################################################################################################

	

	//#################################################################################################################
	//### LOADS ###
	//#################################################################################################################
	string fileBuffer;
	string paramBuffer;
	

	//################################################
	// PLAYER
	//################################################
	//LOAD - PLAYER QT
	playerQt=0;
	if(lines<1){ modal.setMsg("Estrutura do arquivo invalida!\n(PlayerQt not found)");   return false; }
	getline(file, fileBuffer);   lines--;
	if(paramsCount(fileBuffer)!=1){ modal.setMsg("Estrutura do arquivo invalida!\n(PlayerQt line invalid!)");   return false; }
	playerQt=stoi(paramGet(fileBuffer, 1));
	if(playerQt>lines){ modal.setMsg("Estrutura do arquivo invalida!\n(PlayerQt greater than lines in file!)");   return false; }

	//LOAD - PLAYER INFO
	players=new Player[playerQt];
	for(int i=0; i<playerQt; i++){
		getline(file, fileBuffer);   lines--;
		if(paramsCount(fileBuffer)!=6){ modal.setMsg("Estrutura do arquivo invalida!\n(Player line #"+to_string(i+1)+" invalid!)");   return false; }
		players[i].load(paramGet(fileBuffer, 1), paramGet(fileBuffer, 2), stoi(paramGet(fileBuffer, 3)), stoi(paramGet(fileBuffer, 4)), stoi(paramGet(fileBuffer, 5)), stoi(paramGet(fileBuffer, 6)));
		player[i].load(paramGet(fileBuffer, 1), paramGet(fileBuffer, 2), stoi(paramGet(fileBuffer, 3)), stoi(paramGet(fileBuffer, 4)), stoi(paramGet(fileBuffer, 5)), stoi(paramGet(fileBuffer, 6)));
	}


	//################################################
	// ENEMY
	//################################################
	//LOAD - ENEMY QT
	enemyQt=0;
	if(lines<1){ modal.setMsg("Estrutura do arquivo invalida!\n(enemyQt not found)");   return false; }
	getline(file, fileBuffer);   lines--;
	if(paramsCount(fileBuffer)!=1){ modal.setMsg("Estrutura do arquivo invalida!\n(EnemyQt line invalid!)");   return false; }
	enemyQt=stoi(paramGet(fileBuffer, 1));
	if(enemyQt>lines){ modal.setMsg("Estrutura do arquivo invalida!\n(EnemyQt greater than lines in file!)");   return false; }

	//LOAD - ENEMY INFO
	enemies=new Enemy[enemyQt];
	for(int i=0; i<enemyQt; i++){
		getline(file, fileBuffer);   lines--;
		if(paramsCount(fileBuffer)!=6){ modal.setMsg("Estrutura do arquivo invalida!\n(Enemy line #"+to_string(i+1)+" invalid!)");   return false; }
		enemies[i].load(to_string(i)+paramGet(fileBuffer, 1), paramGet(fileBuffer, 2), stoi(paramGet(fileBuffer, 3)), stoi(paramGet(fileBuffer, 4)), stoi(paramGet(fileBuffer, 5)), stoi(paramGet(fileBuffer, 6)));
	}


	//################################################
	// TILE
	//################################################
	//LOAD - TILE QT
	tileQt=0;
	if(lines<1){ modal.setMsg("Estrutura do arquivo invalida!\n(TileQt not found)");   return false; }
	getline(file, fileBuffer);   lines--;
	if(paramsCount(fileBuffer)!=1){ modal.setMsg("Estrutura do arquivo invalida!\n(TileQt line invalid!)");   return false; }
	tileQt=stoi(paramGet(fileBuffer, 1));
	if(tileQt>lines){ modal.setMsg("Estrutura do arquivo invalida!\n(TileQt greater than lines in file!)");   return false; }

	//LOAD - TILE INFO
	tiles=new TileFkn[tileQt];
	for(int i=0; i<tileQt; i++){
		getline(file, fileBuffer);   lines--;
		if(paramsCount(fileBuffer)!=4){ modal.setMsg("Estrutura do arquivo invalida!\n(Tile line #"+to_string(i+1)+" invalid!)");   return false; }
		tiles[i].load(paramGet(fileBuffer, 1), paramGet(fileBuffer, 2), stoi(paramGet(fileBuffer, 3)), stoi(paramGet(fileBuffer, 4)));
	}

	//LOAD - EXTRA TILES
	tilesExtra=new TileFkn[1];
	tilesExtra[0].load("itemCornBagOpen", "images/39-default-gold.png", 1, 1);



	//################################################
	// MAP
	//################################################
	//LOAD - MAP ROWS AND COLS
	extern int mapRows;   extern int mapCols;
	mapRows=0;   mapCols=0;
	if(lines<1){ modal.setMsg("Estrutura do arquivo invalida!\n(Map Rows and Cols not found)");   return false; }
	getline(file, fileBuffer);   lines--;
	if(paramsCount(fileBuffer)!=2){ modal.setMsg("Estrutura do arquivo invalida!\n(Map Rows and Cols line invalid!)");   return false; }
	mapRows=stoi(paramGet(fileBuffer, 1));
	mapCols=stoi(paramGet(fileBuffer, 2));
	if(mapRows>lines){ modal.setMsg("Estrutura do arquivo invalida!\n(Map Rows greater than lines in file!)");   return false; }

	//LOAD - MAP INFO
	extern int **mapTiles;
	mapTiles=new int*[mapRows];
	for(int y=0; y<mapRows; y++){
		mapTiles[y]=new int[mapCols]; }
	for(int y=0; y<mapRows; y++){
		getline(file, fileBuffer);   lines--;
		if(paramsCount(fileBuffer)!=mapCols){ modal.setMsg("Estrutura do arquivo invalida!\n(Map line #"+to_string(y+1)+" invalid!)");   return false; }
		for(int x=0; x<mapCols; x++){
			if(stoi(paramGet(fileBuffer, x+1))>tileQt){ modal.setMsg("Estrutura do arquivo invalida!\n(MapTile line #"+to_string(y+1)+" col #"+to_string(x+1)+" not defined in TileList!)");   return false; }
			mapTiles[y][x]=stoi(paramGet(fileBuffer, x+1));
		}
	}


	//################################################
	// ITENS
	//################################################
	//LOAD - ITENS
	itensQt=0;
	for(int y=0; y<mapRows; y++){ for(int x=0; x<mapCols; x++){   if(mapTiles[y][x]>=3){itensQt++;}   }}
	itens=new Item[itensQt];

	//LOAD - ITENS INFO
	for(int y=0, i=0; y<mapRows; y++){
		for(int x=0; x<mapCols; x++){
			if(mapTiles[y][x]>=3){
				itens[i].load(mapTiles[y][x], x, y);
				i++;
			}
		}
	}
	//#################################################################################################################
	//#################################################################################################################
	//#################################################################################################################


	//DRAW START
	drawStartX=(gJanela.getLargura()/2)-((mapCols*64)/2);
	drawStartY=gJanela.getAltura()-(mapRows*64)-30;


	//SUCCESS
	file.close();
	return true;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Map::unload(){
	//PLAYER
	if(playerQt>0){   for(int i=0; i<playerQt; i++){   players[i].unload();   }   }
	delete[] players;

	//ENEMIES
	if(enemyQt>0){   for(int i=0; i<enemyQt; i++){   enemies[i].unload();   }   }
	delete[] enemies;

	//ITENS
	delete[] itens;

	//TILES
	if(tileQt>0){   for(int i=0; i<tileQt; i++){   tiles[i].unload();   }   }
	delete[] tiles;

	//TILES EXTRA
	tilesExtra[0].unload();
	delete[] tilesExtra;

	//MAP
	extern int mapRows;
	extern int **mapTiles;
	for(int y=0; y<mapRows; y++){
		delete[] mapTiles[y]; }
	delete[] mapTiles;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Map::setPlayer(Player *player){ this->player=player; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
int Map::getRows(){
	extern int mapRows;
	return mapRows; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
int Map::getCols(){
	extern int mapCols;
	return mapCols; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Map::draw(){
	
	extern int mapRows;
	extern int mapCols;
	extern int **mapTiles;

	for(int row=0; row<mapRows; row++){
		for(int col=0; col<mapCols; col++){
			int tile=mapTiles[row][col];
			//EXTRA TILE
			if(tile==39){
				tilesExtra[0].draw(drawStartX+(col*64), drawStartY+(row*64)); }
			//NORMAL TILE
			else{
				if(tile>2){ tile=0; }
				tiles[tile].draw(drawStartX+(col*64), drawStartY+(row*64));
			}
		}
	}
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool Map::run(){
	//##################################################
	//### CONTROL ###
	//##################################################
	
	//TILES
	for(int i=0; i<tileQt; i++){   tiles[i].animate();   }
	
	//PLAYER
	player[0].control(itens, itensQt);
	player[0].animate();
	
	//ENEMIES
	for(int i=0; i<enemyQt; i++){   enemies[i].control();   }
	
	//ITENS
	for(int i=0; i<itensQt; i++){   itens[i].fall();   }
	//##################################################


	//##################################################
	//### COLLISION ###
	//##################################################
	//ITEM x ENEMY
	for(int itemI=0; itemI<itensQt; itemI++){
		for(int enemyI=0; enemyI<enemyQt; enemyI++){
			if(
				itens[itemI].getX() == enemies[enemyI].getX() &&
				itens[itemI].getY() == enemies[enemyI].getY() &&
				itens[itemI].isActive()
			){
				enemies[enemyI].die();
			}
		}
	}
	//ITEM x PLAYER
	for(int itemI=0; itemI<itensQt; itemI++){
		if(
			itens[itemI].getX() == player[0].getX() &&
			itens[itemI].getY() == player[0].getY() &&
			itens[itemI].isActive() &&
			!player[0].isInvulnerable()
		){
			player[0].die();
		}
	}
	//PLAYER x ENEMY
	for(int enemyI=0; enemyI<enemyQt; enemyI++){
		if(
			enemies[enemyI].getX() == player[0].getX() &&
			enemies[enemyI].getY() == player[0].getY() &&
			enemies[enemyI].isActive() &&
			!player[0].isInvulnerable()
		){
			player[0].die();
		}
	}
	//##################################################
	


	//##################################################
	//### DRAW ###
	//##################################################
	//MAP
	draw();

	//ITENS
	for(int i=0; i<itensQt; i++){   itens[i].draw(drawStartX, drawStartY);   }

	//ENEMIES
	for(int i=0; i<enemyQt; i++){   enemies[i].draw(drawStartX, drawStartY);   }

	//PLAYER
	player[0].draw(drawStartX, drawStartY);
	//##################################################


	
	//##################################################
	//### END LEVEL ###
	//##################################################
	extern int mapRows;
	extern int mapCols;
	extern int **mapTiles;

	for(int row=0; row<mapRows; row++){
		for(int col=0; col<mapCols; col++){
			if(mapTiles[row][col]==2){
				//CONTINUE
				return true;
			}
		}
	}
	//END
	return false;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################


