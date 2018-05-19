#include "KeypadComponent.h"
#include "Code.h"
#include "PlayState.h"
#include "Door.h"
#include "MessageTrigger.h"
#include "KeyPadController.h"
#include "KeypadState.h"

KeypadComponent::KeypadComponent(Texture* image, Entity* codeEntity, int password) : numpad_ (image)
{
	codeEntity_ = codeEntity;
	password_ = to_string(password);
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	h = (float)(Game::Instance()->getWindowHeight()) / (float)(numpad_->getHeight());
	w = (float)(Game::Instance()->getWindowWidth() / 3 + 100) / (float)(numpad_->getWidth());

	background_ = resource->getTexture("Background");

	dest.h = numpad_->getHeight() * h;
	dest.w = numpad_->getWidth() * w;

	dest.x = (Game::Instance()->getWindowWidth() / 2) - (dest.w / 2);
	dest.y = 0;

	//Screen
	screen = KeypadScreen(pRenderer, h, w);

	//Botones del teclado
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j] = NumberKey(pRenderer, i* 3 + j + 1, i, j, h, w);
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
		keys[3][j] = NumberKey(pRenderer, value, 3, j, h, w);
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
			if (codeEntity_ != nullptr)
				codeEntity_->getComponent<Code>()->setCodeActive(false);
			KeypadState::Instance()->setPop(true);
		}
	}
}
void KeypadComponent::update(Entity* e, Uint32 time) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j].update(time);
		}
	}
	screen.update(time);

}


void KeypadComponent::render(Entity* e, Uint32 time) {

	//Pinta el teclado
	if (pc == nullptr)
		pc = Game::Instance()->getEntityWithComponent<KeyPadController>()->getComponent<KeyPadController>();

	background_->render(pRenderer, { 0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight() }, nullptr);

	numpad_->render(pRenderer, dest, nullptr);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			keys[i][j].render(time);
		}
	}
	screen.render(time);

	if (pc != nullptr && pc->joysticksInitialised() && pc->getActive()) {
		dest = { keys[markSlot.y][markSlot.x].getNumRect().x - 5, keys[markSlot.y][markSlot.x].getNumRect().y -5,
			keys[markSlot.y][markSlot.x].getNumRect().w +10, keys[markSlot.y][markSlot.x].getNumRect().h +10 };	//El borde
		renderMark(dest);
	}
}

void KeypadComponent::addNumber(int n) {
	sequence_ += to_string(n);
	screen.setSequence(sequence_);
	Game::Instance()->getResourceManager()->getSound("BeepSound")->play();
}

void KeypadComponent::validCode()
{
	if (validate())
	{
		codeEntity_->getComponent<Code>()->setAccept(true);
		codeEntity_->getComponent<Code>()->setCodeActive(false);
		codeEntity_->getComponent<MessageTrigger>()->setMessage("");
		for (Entity* e : *(PlayState::Instance()->getDoors()))
		{
			if (e->getComponent<Door>()->getDoorNum() == codeEntity_->getComponent<Code>()->getNumDoorCode())
				e->getComponent<Door>()->keyFalse();
		}
		//cout << "Nice" << endl;
		Game::Instance()->getResourceManager()->getSound("CodeSuccessSound")->play();
		KeypadState::Instance()->setPop(true);
	}
	else {
		//cout << "Wrong" << endl;
		clear();
		Game::Instance()->getResourceManager()->getSound("ErrorCodeSound")->play();
	}
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

void KeypadComponent::renderMark(SDL_Rect DestRect)
{
	resource->getTexture("InventoryCursor")->render(pRenderer, DestRect);	//Aqui es la textura del borde
}

void KeypadComponent::moveMarkSlot(int a)
{
	if (a == 1) {
		if (markSlot.y > 0) {
			markSlot.y--;
		}
	}
	else if (a == 3) {
		if (markSlot.y < 3) {
			markSlot.y++;
		}
	}
	else if (a == 2) {
		if (markSlot.x < 2) {
			markSlot.x++;
		}
	}
	else if (a == 4) {
		if (markSlot.x > 0) {
			markSlot.x--;
		}
	}
}

void KeypadComponent::clickMark()
{
	if (markSlot.y < 3) {
		if (markSlot.y == 0 && markSlot.x == 0) {
			addNumber(1);
		}
		else if (markSlot.y == 0 && markSlot.x == 1) {
			addNumber(2);
		}
		else if (markSlot.y == 0 && markSlot.x == 2) {
			addNumber(3);
		}
		else if (markSlot.y == 1 && markSlot.x == 0) {
			addNumber(4);
		}
		else if (markSlot.y == 1 && markSlot.x == 1) {
			addNumber(5);
		}
		else if (markSlot.y == 1 && markSlot.x == 2) {
			addNumber(6);
		}
		else if (markSlot.y == 2 && markSlot.x == 0) {
			addNumber(7);
		}
		else if (markSlot.y == 2 && markSlot.x == 1) {
			addNumber(8);
		}
		else if (markSlot.y == 2 && markSlot.x == 2) {
			addNumber(9);
		}		
	}
	if (markSlot.y == 3 && markSlot.x == 1)
		addNumber(0);
	if (markSlot.y == 3 && markSlot.x == 0)
		clear();
	if (markSlot.y == 3 && markSlot.x == 2)
		validCode();
}
