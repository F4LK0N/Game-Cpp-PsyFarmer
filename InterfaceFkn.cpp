#include "InterfaceFkn.h"



//#####################################################################################################################################################################
InterfaceFkn::InterfaceFkn(){}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
InterfaceFkn::~InterfaceFkn(){}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void InterfaceFkn::init(){
	score.setFonte("fScore");
	score.setAncora(0, 0);
	gRecursos.carregarSpriteSheet("interfaceLife", "_internal/images/life.png", 1, 1);
	life.setSpriteSheet("interfaceLife");
	life.setAncora(1, 0);
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void InterfaceFkn::draw(Player *player){
	
	//TOP BAR
	for(int i=0; i<50; i++){ gGraficos.desenharLinha(0, i, gJanela.getLargura(), i, 0, 0, 255, 200); }

	//SCORE
	score.setString(to_string(player[0].getScore()));
	score.desenhar(40, 8);

	//LIFES
	for(int i=0; i<player[0].getLifes(); i++){   life.desenhar(gJanela.getLargura()-(i*40)-25, 8);   }
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################