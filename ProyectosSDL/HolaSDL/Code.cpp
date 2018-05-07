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
	if (!e->getComponent<Code>()->getAccept()) {
		e->getComponent<Code>()->setCodeActive(true);
		Game::Instance()->getStateMachine()->pushState(KeypadState::Instance());
	}
}

void Code::load(int numDoor, int code)
{
	numDoor_ = numDoor;
	code_ = code;
	codeActive_ = false;
	accept_ = false;
}
