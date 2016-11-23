#include "Jogo.h"

Jogo::Jogo(){}

Jogo::~Jogo(){}

//#####################################################################################################################################################################
void Jogo::inicializar()
{
	//TELA
	uniInicializar(800, 600, true);
	//uniInicializar(1024, 768, true);
	//uniInicializar(1024, 600, false);
	//uniInicializar(1024, 768, true);
	//uniInicializar(1920, 1080, true);

	//RANDOM NUMBERS
	srand(time(0));

	//INSTANCES
	running=rMenu;
	runningLast=rMenu;
	runningMenu=mMain;

	//#####################################################################################
	// RESOURCES
	//#####################################################################################
	//FONTS
	gRecursos.carregarFonte("fArial",     "fonte_padrao.ttf");//DELETE-ME
	gRecursos.carregarFonte("fArialMini", "fonte_padrao.ttf", 10);//DELETE-ME
	gRecursos.carregarFonte("fMenuBig",  "fonte_padrao.ttf", gJanela.getLargura()/20);
	gRecursos.carregarFonte("fMenu",     "fonte_padrao.ttf", gJanela.getLargura()/40);
	gRecursos.carregarFonte("fMenuMini", "fonte_padrao.ttf", gJanela.getLargura()/60);
	gRecursos.carregarFonte("fScore",    "fonte_padrao.ttf", gJanela.getLargura()/40);
	//SOUNDS
	gRecursos.carregarAudio("somClick", "assets/sounds/click.mp3");
	//SPRITES
	gRecursos.carregarSpriteSheet("ITEMcornBag",   "_internal/images/3-default-gold.png",  1,  5);
	gRecursos.carregarSpriteSheet("ITEMagrotoxic", "_internal/images/4-default-pedra.png", 1, 10);
	gRecursos.carregarSpriteSheet("ITEMspecial",   "_internal/images/4-default-pedra.png", 1, 10);


	//#####################################################################################
	// MENUS
	//#####################################################################################
	menu[mMain].addItem("Jogar");
	//menu[mMain].addItem("DLCs");
	menu[mMain].addItem("Creditos");
	menu[mMain].addItem("Sair");
	//#####################################################################################
	menu[mPause].addItem("Continuar Jogo");
	menu[mPause].addItem("Ir para o Menu");
	menu[mPause].addItem("Sair para o Windows");
	//#####################################################################################
	menu[mLevelEnd].addItem("Continuar Jogo");
	menu[mLevelEnd].addItem("Ir para o Menu");
	menu[mLevelEnd].addItem("Sair para o Windows");
	//#####################################################################################
	menuText.setFonte("fMenu");
	menuWait=0;
	//#####################################################################################

	//#####################################################################################
	// PLAYER
	//#####################################################################################
	player=new Player;//change to not pointer
	map.setPlayer(player);//???? vaio precisar disso? como vai ser?

	//#####################################################################################
	// INTERFACE
	//#####################################################################################
	interfaceFkn.init();
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::finalizar()
{
	//STOP MUSICS
	gMusica.parar();

	//WAIT FOR ANY OTHER SOUNDS
	_sleep(1000);

	//UNLOAD RESOURCES
	gRecursos.descarregarTodasFontes();
	gRecursos.descarregarTodasMusicas();
	gRecursos.descarregarTodosAudios();
	gRecursos.descarregarTodosSpriteSheets();
	gRecursos.descarregarTudo();

	uniFinalizar();
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################


	


//#####################################################################################################################################################################
void Jogo::executar(){   while(running!=rExit && !gEventos.sair){
	uniIniciarFrame();

		//### MODAL ###
		if(running==rModal){
			if(!modal.run()){ running=runningLast; }   }
	
		//### MENUS ###
		else if(running==rMenu){ 
			if(menuWait>0){ menuWait--; }
			else{switch(runningMenu){
				case mPause:    menuPause();    break;
				case mMain:     menuMain();     break;
				case mGameOver: menuGameOver(); break;
				case mGameEnd:  menuGameEnd();  break;
				case mLevelEnd: menuLevelEnd(); break;
				case mCredits:  menuCredits(); break;
			}}
		}
	
		//### GAME ###
		else if(running==rGame){ 
			runGame();
		}
	
	uniTerminarFrame();
}}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################





//#####################################################################################################################################################################
void Jogo::menuMain(){ switch(menu[mMain].run()){

	//### JOGAR ###
	case 0:
		//LOAD MAP LIST
		if(!mapList.load("_internal/0-level.list", modal)){
			//ERROR
			modal.setMsg("Não foi possivel carregar a lista de mapas!\n\nMotivo:\n"+modal.getMsg());
			running=rModal;
			runningLast=rMenu;
			break; }

		//LOAD MAP
		if(!map.load("_internal/"+mapList.get(), modal)){
			//ERROR
			modal.setMsg("Não foi possivel carregar o mapa!\n\nMotivo:\n"+modal.getMsg());
			running=rModal;
			runningLast=rMenu;
			break; }

		//PLAYER
		player[0].reset();
		
		//RUN GAME
		running=rGame;
	break;
	//### ### ### ###

	//### CREDITS ###
	case 1:
		running=rMenu;
		runningMenu=mCredits;
	break;
	//### ### ### ###

	//### EXIT GAME ###
	case 2:   running=rExit;   break;
	//### ### ### ###
}}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::menuPause(){ switch(menu[mPause].run()){

	//### JOGAR ###
	case 0:   running=rGame;   break;
	//### ### ### ###

	//### BACK TO MENU ###
	case 1:   
		map.unload();
		runningMenu=mMain;
	break;
	//### ### ### ###

	//### EXIT GAME ###
	case 2:   running=rExit;   break;
	//### ### ### ###
}}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::menuGameOver(){

	menuText.setAncora(0.5, 0.5);
	menuText.setString("Game Over");
	menuText.desenhar(gJanela.getLargura()/2, gJanela.getAltura()/2);

	//### EXIT ###
	if(gTeclado.pressionou[TECLA_ESC] || gTeclado.pressionou[TECLA_ENTER]){
		runningMenu=mMain; }
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::menuGameEnd(){

	menuText.setAncora(0.5, 0.5);
	menuText.setString("Parabens!!!\nVocê finalizou todas as fases!\n\n\nSua pountuação:\n"+to_string(player[0].getScore()));
	menuText.desenhar(gJanela.getLargura()/2, gJanela.getAltura()/2);

	//### EXIT ###
	if(gTeclado.pressionou[TECLA_ESC] || gTeclado.pressionou[TECLA_ENTER]){
		runningMenu=mMain; }
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::menuLevelEnd(){

	menuText.setAncora(0.5, 0.5);
	menuText.setString("Você completou a fase!\n\n\n              Deseja continuar?");
	menuText.desenhar(gJanela.getLargura()/2, gJanela.getAltura()/2);

	switch(menu[mPause].run()){
		//### JOGAR ###
		case 0:   running=rGame;   break;
		//### ### ### ###

		//### BACK TO MENU ###
		case 1:
			map.unload();
			runningMenu=mMain;
		break;
		//### ### ### ###

		//### EXIT GAME ###
		case 2:   running=rExit;   break;
		//### ### ### ###
	}
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
bool Jogo::runGame(){
	
	//BACKGROUND
	//...
	
	//MAP
	if(!map.run()){
		//UNLOAD
		map.unload();
		
		//### NEXT MAP ###
		if(mapList.next()){
			running=rMenu;
			runningMenu=mLevelEnd;
			menuWait=60;
			
			//LOAD MAP
			if(!map.load("_internal/"+mapList.get(), modal)){
				map.unload();//passar este unload para verificações melhores dentro do map.load
				//ERROR
				modal.setMsg("Não foi possivel carregar o proximo mapa!\n\nMotivo:\n"+modal.getMsg());
				running=rModal;
				runningLast=rMenu;
				runningMenu=mMain;
				return true; }
			return true;
		}
		
		//### GAME END ###
		else{
			running=rMenu;
			runningMenu=mGameEnd;
			menuWait=60; 
			return true; }
	}

	//INTERFACE
	interfaceFkn.draw(player);



	//### GAME OVER ###
	if(player[0].getLifes()<1){
		running=rMenu;
		runningMenu=mGameOver; 
		map.unload(); }

	
	//### PAUSE ###
	if(gTeclado.pressionou[TECLA_ESC]){
		running=rMenu;
		runningMenu=mPause; }

	
	//### KEEP RUNNING ###
	return true;
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################



//#####################################################################################################################################################################
void Jogo::menuCredits(){

	menuText.setAncora(0.5, 0.5);
	menuText.setString(
		"Alunos:\n"
		"   Arthur Reolon\n"
		"   Otávio Sória\n"
		"\n\n\n"
		"Professor:\n"
		"   Fernando Pinho Marson\n"
		"\n\n\n"
		"Software:\n"
		"   LibUnicornio\n"
		"   C++\n"
	);
	menuText.desenhar(gJanela.getLargura()/2, gJanela.getAltura()/2);

	//### EXIT ###
	if(gTeclado.pressionou[TECLA_ESC] || gTeclado.pressionou[TECLA_ENTER]){
		runningMenu=mMain; }
}
//#####################################################################################################################################################################
//#####################################################################################################################################################################
//#####################################################################################################################################################################


	

