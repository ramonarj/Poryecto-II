#include "GameState.h"
#include "Game.h"

unique_ptr<GameState> GameState::s_pInstance = nullptr;

GameState::GameState(){ //Constructora
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

void GameState::removeEntity(Entity* e) {
	removedEntities_.push_back(e);
}
void GameState::removeStage(Entity* e) {
	stage_.remove(e);
}
void GameState::removeInteractible(Entity* e) {
	interactibles_.remove(e);
}
void GameState::removeCharacter(Entity* e) {
	characters_.remove(e);
}
void GameState::removeDoor(Entity* e) {
	doors_.remove(e);
}

void GameState::removeEntities() {
	for (Entity* e : removedEntities_) {
		removeStage(e);
		removeInteractible(e);
		removeCharacter(e);
		removeDoor(e);
		delete(e);
	}
	removedEntities_.clear();
}