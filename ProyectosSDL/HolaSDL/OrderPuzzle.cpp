#include "OrderPuzzle.h"
#include "Game.h"

unique_ptr<OrderPuzzle> OrderPuzzle::s_pInstance = nullptr;

OrderPuzzle::OrderPuzzle()
{
}

OrderPuzzle::~OrderPuzzle()
{
}

void OrderPuzzle::startState()
{
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());

	Entity* orderpuzzle = new Entity(0, 0);
	orderpuzzle->addComponent(new OrderPuzzleComponent());
	stage_.push_back(orderpuzzle);

}

void OrderPuzzle::render(Uint32 time)
{
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void OrderPuzzle::update(Uint32 time)
{
	GameState::update(time);
}

void OrderPuzzle::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}
