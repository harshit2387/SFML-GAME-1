//#include <SFML/Graphics.hpp>

#include<iostream>
#include "Game.h"
using namespace std;
using namespace sf;
int main(int argc,char*argv[]){
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));
	
   //Init game Engine
    Game game;
	while(game.running() && !game.getEndGame()){
		game.update();
		game.render();
	}
	return 0;
}



