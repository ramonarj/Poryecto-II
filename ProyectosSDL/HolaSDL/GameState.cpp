#include "GameState.h"
#include "Game.h"

GameState* GameState::s_pInstance = 0;

GameState::GameState(Game* game): game_(game){ //Constructora
}

GameState::~GameState(){ //Destructora
	for (Entity* o : stage_)
		delete o;
}

void GameState::startState()
{
}

void GameState::render(Uint32 time){ //Llama a los render components de todas las entities
	for (Entity* e : stage_)
		e->render(time);
}

void GameState::update(Uint32 time) { //Llamar a los logic components de todas las entities
	for (Entity* e : stage_)
		e->update(time);
}

void GameState::handleInput(Uint32 time, SDL_Event& event) { //Llamar a los input components de todas las entities
	for (Entity* e : stage_)
		e->handleInput(time, event);
}