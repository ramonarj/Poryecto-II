#include "OrderPuzzle.h"
#include "Game.h"
#include "Countdown.h"
#include "Order.h"

OrderPuzzle* OrderPuzzle::s_pInstance = nullptr;

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

	list<Entity*>::iterator it;
	bool foundPuzzle = false;
	Entity* puzzleEntity = nullptr;
	for (it = PlayState::Instance()->getOrderPuzzles()->begin(); it != PlayState::Instance()->getOrderPuzzles()->end() && !foundPuzzle; it++)
	{
		if ((*it)->getComponent<Order>()->getPuzzleActive())
		{
			foundPuzzle = true;
			puzzleEntity = (*it);
		}
	}

	Entity* orderpuzzle = new Entity(0, 0);
	orderpuzzle->addComponent(new OrderPuzzleComponent(puzzleEntity));
	orderpuzzle->addComponent(new OrderPuzzleController());
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
	if (pop_)
		Game::Instance()->stateMachine_.popState();
}

void OrderPuzzle::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}
