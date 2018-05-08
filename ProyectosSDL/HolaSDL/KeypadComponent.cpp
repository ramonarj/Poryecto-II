#include "KeypadComponent.h"
#include "Code.h"
#include "PlayState.h"
#include "Door.h"


KeypadComponent::KeypadComponent(Texture* image, Entity* codeEntity, int password) : numpad_ (image)
{
	codeEntity_ = codeEntity;
	password_ = to_string(password);
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	dest.x = dest.y = 0;
	dest.h = numpad_->getHeight();
	dest.w = numpad_->getWidth();
	//Screen
	screen = KeypadScreen(pRenderer);

	//Botones del teclado
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j] = NumberKey(pRenderer, i* 3 + j + 1, i, j, 50, 50, 100);
		}
	}
	for (int j = 0; j < 3; j++) {
		int value;
		switch (j)
		{
		case 0:
			value = 10;
			break;
		case 1:
			value = 0;
			break;
		case 2:
			value = 11;
			break;
		}
		keys[3][j] = NumberKey(pRenderer, value, 3, j, 50, 50, 100);
	}
}


void KeypadComponent::handleInput(Entity* e, Uint32 time, const SDL_Event& event) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int i = 0;
			bool clicked = false;
			while (i < 4 && !clicked) {
				int j = 0;
				while (j < 3 && !clicked) {
					clicked = keys[i][j].clicked(event.button.x, event.button.y, time);
					if (clicked){
						int n = 3 * i + j + 1;
						if (sequence_.size() < 4) {
							if (n < 10)
								addNumber(n);
							else if (n == 11)
								addNumber(0);
						}
						if (n == 10)
							clear();
						else if(n == 12) {
							validCode();
						}
					}
					j++;
				}
				i++;
			}
		}
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (state[SDL_SCANCODE_E])
		{
			codeEntity_->getComponent<Code>()->setCodeActive(false);
			Game::Instance()->getStateMachine()->changeState(PlayState::Instance());
		}
	}
}
void KeypadComponent::update(Entity* e, Uint32 time) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j].update(time);
		}
	}
}


void KeypadComponent::render(Entity* e, Uint32 time) {
	//Pinta el teclado
	numpad_->render(pRenderer, dest, nullptr);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j].render(time);
		}
	}
	screen.render(time);
}

void KeypadComponent::addNumber(int n) {
	sequence_ += to_string(n);
	screen.setSequence(sequence_);
}

void KeypadComponent::validCode()
{
	if (validate())
	{
		codeEntity_->getComponent<Code>()->setAccept(true);
		codeEntity_->getComponent<Code>()->setCodeActive(false);
		list<Entity*> doors = (*PlayState::Instance()->getDoors());
		for (Entity* e : *(PlayState::Instance()->getDoors()))
		{
			if (e->getComponent<Door>()->getDoorNum() == codeEntity_->getComponent<Code>()->getNumDoorCode())
				e->getComponent<Door>()->keyFalse();
		}
		cout << "Nice" << endl;
		Game::Instance()->getStateMachine()->changeState(PlayState::Instance());
	}
	else
		cout << "Wrong" << endl;
}

bool KeypadComponent::validate() {
	return (sequence_ == password_) ? true : false;
}
void KeypadComponent::clear() {
	sequence_ = "";
	screen.setSequence(sequence_);

}

KeypadComponent::~KeypadComponent()
{
}
