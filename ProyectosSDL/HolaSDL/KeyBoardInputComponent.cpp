#include "KeyBoardInputComponent.h"



KeyBoardInputComponent::KeyBoardInputComponent()
{
}

KeyBoardInputComponent::KeyBoardInputComponent(SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down, SDL_Scancode interact, SDL_Scancode attack, SDL_Scancode inventory, SDL_Scancode pause, SDL_Scancode enter) :
	left_(left), right_(right), up_(up), down_(down), interact_(interact), attack_(attack), inventory_(inventory), pause_(pause), enter_(enter) {
}

KeyBoardInputComponent::~KeyBoardInputComponent()
{
}

void KeyBoardInputComponent::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {

	Vector2D velocity = o->getVelocity();

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[left_]) {
		velocity.setX(-1);
	}
	else if (state[right_]) {
		velocity.setX(1);
	}
	else {
		velocity.setX(0);
	}
	if (state[up_]) {
		velocity.setY(-1);
	}
	else if (state[down_]) {
		velocity.setY(1);
	}
	else if (state[interact_]) {
		//INTERACTUAR ETC
	}
	else {
		velocity.setY(0);
	}

	o->setVelocity(velocity);

}
