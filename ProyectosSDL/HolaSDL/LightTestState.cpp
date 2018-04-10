#include "LightTestState.h"
#include "StaticImageRender.h"

LightTestState::LightTestState(Game* game_) {
	Entity* textTest = new Entity(0, 0);
	textTest->addComponent(new StaticImageRender(game_->getResourceManager()->getTexture("Inventory")));
	textTest->setHeight(game_->getWindowHeight());
	textTest->setWidth(game_->getWindowWidth());
	stage_.push_back(textTest);
}

LightTestState::~LightTestState() {
}

void LightTestState::update(Uint32 time)
{
	GameState::update(time);
}

void LightTestState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	cout << stage_.size() << endl;
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void LightTestState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}