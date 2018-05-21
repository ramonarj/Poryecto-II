#include "GameState.h"
#include "Game.h"

unique_ptr<GameState> GameState::s_pInstance = nullptr;

GameState::GameState() { //Constructora
}

GameState::~GameState() { //Destructora
	while (!stage_.empty()) {
		Entity* temp = stage_.front();
		stage_.pop_front();
		delete temp;
	}

	while (!interactibles_.empty()) {
		interactibles_.pop_front();
	}

	while (!characters_.empty()) {
		characters_.pop_front();
	}

	while (!removedEntities_.empty()) {
		removedEntities_.pop_front();
	}

	while (!removedInteractibles_.empty()) {
		removedInteractibles_.pop_front();
	}

	while (!codes_.empty()) {
		codes_.pop_front();
	}

	while (!orderPuzzles_.empty()) {
		orderPuzzles_.pop_front();
	}

	if (cursor_ != nullptr)	delete cursor_;
}

void GameState::startState()
{
}

void GameState::render(Uint32 time) { //Llama a los render components de todas las entities
	for (Entity* e : stage_)
		e->render(time);
	if (cursor_ != nullptr)
		cursor_->render(time);
}

void GameState::update(Uint32 time) { //Llamar a los logic components de todas las entities
	for (Entity* e : stage_)
		e->update(time);
}

void GameState::handleInput(Uint32 time, SDL_Event& event) { //Llamar a los input components de todas las entities
	for (Entity* e : stage_)
		e->handleInput(time, event);
	if (cursor_ != nullptr)
		cursor_->handleInput(time,event);
}

void GameState::saveToFile()
{
	for (Entity* e : stage_)
		e->saveToFile();
}

void GameState::loadToFile()
{
	for (Entity* e : stage_)
		e->loadToFile();
}

void GameState::mergeStages()
{
	for (Entity* e : stageAux_)
		stage_.push_back(e);
}

void GameState::removeEntity(Entity* e) {
	removedEntities_.push_back(e);
}
void GameState::removeStage(Entity* e) {
	stage_.remove(e);
}
void GameState::removeStageAux(Entity * e)
{
	stageAux_.remove(e);
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
	
	for (Entity* e : removedInteractibles_) {
		e->setActive(false);
	}
}

void GameState::removeInteractibleOfStage(Entity* e) {
	removedInteractibles_.push_back(e);
}
