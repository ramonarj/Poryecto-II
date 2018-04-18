#include "LightTestState.h"
#include "StaticImageRender.h"
#include "LightManager.h"
#include "Light.h"

LightTestState::LightTestState(Game* game_) {
	Entity* fondo = new Entity(0, 0);
	fondo->addComponent(new StaticImageRender(game_->getResourceManager()->getTexture("BGtest")));
	fondo->setHeight(game_->getWindowHeight());
	fondo->setWidth(game_->getWindowWidth());
	stage_.push_back(fondo);

	Entity* lightManagerEntity = new Entity(0, 0);
	LightManager* lightManager = new LightManager();
	lightManagerEntity->addComponent(lightManager);
	lightManagerEntity->setHeight(game_->getWindowHeight());
	lightManagerEntity->setWidth(game_->getWindowWidth());
	stage_.push_back(lightManagerEntity);

	lightManager->addLight(new Light(game_->getResourceManager()->getTexture("PointLight"), 0, 0));
	lightManager->addLight(new Light(game_->getResourceManager()->getTexture("PointLight"), -400, -400));
}

LightTestState::~LightTestState() {
}

void LightTestState::startState() {
	//CURSOR
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());
	cursor_->setActive(false);
}

void LightTestState::update(Uint32 time)
{
	GameState::update(time);
}

void LightTestState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void LightTestState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}