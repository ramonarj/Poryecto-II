#include "KeypadState.h"
#include "Code.h"

unique_ptr<KeypadState> KeypadState::s_pInstance = nullptr;

KeypadState::KeypadState()
{
}
void KeypadState::startState() {
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());

	int numCode = 0;
	Entity* codeEntity = nullptr;
	list<Entity*>::iterator it;
	bool foundCode = false;
	for (it = codes_.begin(); it != codes_.end() && !foundCode; it++)
	{
		if ((*it)->getComponent<Code>()->getCodeActive())
		{
			foundCode = true;
			numCode = (*it)->getComponent<Code>()->getNumCode();
			codeEntity = (*it);
		}
	}
	Entity* keypad = new Entity(0, 0);
	keypad->addComponent(new KeypadComponent(Game::Instance()->getResourceManager()->getTexture("Keypad"), codeEntity, numCode));
	stage_.push_back(keypad);
}

void KeypadState::render(Uint32 time)
{
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void KeypadState::update(Uint32 time)
{
	GameState::update(time);
}

void KeypadState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}

KeypadState::~KeypadState()
{
}
