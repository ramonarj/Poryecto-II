#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* game): game_(game){ //Constructora
}

GameState::~GameState(){ //Destructora
	for (GameObject* o : stage) delete o;
}

void GameState::render(Uint32 time){
	//Llamar a los render components de todas las entities
}

void GameState::update() {
	//Llamar a los logic components de todas las entities
}

void GameState::handleEvent(SDL_Event& event) {
	//Llamar a los input components de todas las entities
}