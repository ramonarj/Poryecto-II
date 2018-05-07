#include "Code.h"
#include "Game.h"
#include "KeypadState.h"


Code::Code() : Interactible(), numDoor_(0), code_(0), codeActive_(false), accept_(false)
{
}


Code::~Code()
{
}

void Code::interact(Entity * e)
{
	if (canWriteCode())
	{
		if (!e->getComponent<Code>()->getAccept()) {
			e->getComponent<Code>()->setCodeActive(true);
			Game::Instance()->getStateMachine()->pushState(KeypadState::Instance());
		}
	}
}

void Code::load(int numDoor, int code, string dir)
{
	numDoor_ = numDoor;
	code_ = code;
	ori_ = dir;
	codeActive_ = false;
	accept_ = false;
}

bool Code::canWriteCode()
{
	PlayerAnimationComponent* animPlayer = PlayState::Instance()->getPlayer()->getComponent<PlayerAnimationComponent>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}
