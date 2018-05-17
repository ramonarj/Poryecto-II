#include "Order.h"
#include "Game.h"
#include "OrderPuzzle.h"
#include "Door.h"
#include "MessageTrigger.h"

Order::Order(): puzzleActive_(false)
{
}


Order::~Order()
{
}


bool Order::interact(Entity * e)
{
	if (!puzzleComplete_) {
		Game::Instance()->getStateMachine()->pushState(OrderPuzzle::Instance());
		puzzleActive_ = true;
	}
	return true;
}

void Order::setPuzzleComplete(bool b)
{
	puzzleComplete_ = b;
	for (Entity* e : *(PlayState::Instance()->getDoors()))
	{
		if (e->getComponent<Door>()->getDoorNum() == 1000)
		{
			if (puzzleComplete_)
				e->getComponent<Door>()->keyFalse();
			else
			{
				e->getComponent<Door>()->keyTrue();
				e->getComponent<MessageTrigger>()->setMessage("Parece que esta puerta está averiada");
			}
		}
	}
}
