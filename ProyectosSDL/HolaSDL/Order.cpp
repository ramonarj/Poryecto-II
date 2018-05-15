#include "Order.h"
#include "Game.h"
#include "OrderPuzzle.h"

Order::Order(): puzzleActive_(false)
{
}


Order::~Order()
{
}


bool Order::interact(Entity * e)
{
	Game::Instance()->getStateMachine()->pushState(OrderPuzzle::Instance());
	puzzleActive_ = true;
	return true;
}