#include "Enemy.h"



//#####################################################################################################################################################################
Enemy::Enemy(){
	status=true;
	spritesheetName="";
	imagePath="";
	animations=0;
	frames=0;
	x=0;
	y=0;
	moving=true;
	drawX=0;
	drawY=0;
	spritesheet.setAncora(0, 0);

	moveDelay=((rand()%4)+1)*250;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
Enemy::~Enemy(){}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Enemy::load(string spritesheetName, string imagePath, int animations, int frames, int x, int y)
{
	this->spritesheetName=spritesheetName;
	this->imagePath=imagePath;
	this->animations=animations;
	this->frames=frames;
	this->x=x;
	this->y=y;

	//CHECK SPRITESHEET
	unload();
	ifstream file;
	do{
		//DLC
		file.open("dlcs/"+imagePath);
		if(file.is_open()){
			this->imagePath="dlcs/"+imagePath;
			break; }

		//INTERNAL
		file.open("_internal/"+imagePath);
		if(file.is_open()){
			this->imagePath="_internal/"+imagePath;
			break; }

		//DEFAULT
		this->animations=1;
		this->frames=4;
		this->imagePath="_internal/images/000-default-enemy.png";

	}while(false);//<-- Sorry about this :P
	file.close();


	//LOAD SET SPRITESHEET (ATEN��O: Este comando este retornando sempre false =/)
	if(!gRecursos.carregouSpriteSheet(this->spritesheetName)){ gRecursos.carregarSpriteSheet(this->spritesheetName, this->imagePath, this->animations, this->frames); }
	this->spritesheet.setSpriteSheet(this->spritesheetName);
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Enemy::unload(){
	if(this->spritesheetName!=""){
		gRecursos.descarregarSpriteSheet(this->spritesheetName);   }}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool Enemy::move(int dirX, int dirY){

	if(!status || moving){ return false; }

	extern int **mapTiles;
	extern int mapRows;
	extern int mapCols;

	int targetX=(x+dirX);
	int targetY=(y+dirY);
	if(targetX<0 || targetX>mapCols-1){ return false; }
	if(targetY<0 || targetY>mapRows-1){ return false; }

	//BLOCKED
	if(mapTiles[targetY][targetX]!=0){ return false; }

	//MOVE
	x=targetX;   y=targetY;
	drawX+=64*dirX*-1;   drawY+=64*dirY*-1;
	moving=true;
	return true;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Enemy::control(){
	if(!status || moving){ return; }

	switch(rand()%moveDelay){
		case 0:   move(0,-1);   break;
		case 1:   move(0, 1);   break;
		case 2:   move(-1,0);   break;
		case 3:   move( 1,0);   break;
	}

}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Enemy::draw(int canvasStartX, int canvasStartY){
	if(!status){ return; }

	//Moving
	if(drawX>0){ drawX-=1; }else if(drawX<0){ drawX+=1; }
	if(drawY>0){ drawY-=1; }else if(drawY<0){ drawY+=1; }
	//Stop
	if(drawX==0 && drawY==0){
		moving=false; }
	//Draw
	spritesheet.desenhar(canvasStartX+drawX+(this->x*64), canvasStartY+drawY+(this->y*64));

	//Anim
	if(moving){ spritesheet.avancarAnimacao(); }
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Enemy::die(){ status=false; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
int Enemy::getX(){ return x; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
int Enemy::getY(){ return y; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool Enemy::isActive(){ return status; }
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################