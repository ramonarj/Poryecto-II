#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* game): game_(game){ //Constructora
}

GameState::~GameState(){ //Destructora
	for (Entity* o : stage)
		delete o;
}

void GameState::render(Uint32 time){ //Llama a los render components de todas las entities
	for (Entity* e : stage)
		e->render(time);
}

void GameState::update(Uint32 time) { //Llamar a los logic components de todas las entities
	for (Entity* e : stage)
		e->update(time);
}

void GameState::handleEvent(Uint32 time, SDL_Event& event) { //Llamar a los input components de todas las entities
	for (Entity* e : stage)
		e->handleInput(time, event);
}