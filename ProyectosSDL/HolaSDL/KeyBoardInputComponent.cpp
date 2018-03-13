#include "KeyBoardInputComponent.h"
#include "ImageRenderer.h"
#include <iostream>


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
	Vector2D direction = o->getDirection();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[left_] && !(o->getComponent<Character>()->getAttacking())) {		//ESTO SE PODRIA AGRUPAR COMO CONDICIONE GENERAL YA QUE SI ESTAS ATACANDO TAMPOCO DEBERIAS PODER HACER OTRAS COSAS
		velocity.setX(-10);
		direction.setX(-1);
	}
	else if (state[right_] && !(o->getComponent<Character>()->getAttacking())) {
		velocity.setX(10);
		direction.setX(1);
	}
	else {
		velocity.setX(0);
		direction.setX(0);
	}
	if (state[up_] && !(o->getComponent<Character>()->getAttacking())) {
		velocity.setY(-10);
		direction.setY(1);
	}
	else if (state[down_] && !(o->getComponent<Character>()->getAttacking())) {
		velocity.setY(10);
		direction.setY(-1);
	}
	else if (state[interact_]) {
		if (event.type == SDL_KEYDOWN) {
			SDL_Rect playerRect = { int(o->getPosition().getX()), int(o->getPosition().getX()), int(o->getWidth()), int(o->getHeight()) };
			for (Entity* e : *Game::Instance()->stateMachine_.currentState()->getInteractibles()) {
				SDL_Rect intRect = { int(e->getPosition().getX()), int(e->getPosition().getX()), int(e->getWidth()), int(e->getHeight()) };
				if (Collisions::RectRect(&playerRect, &intRect)) {
					if (e->getComponent<Interactible>() != nullptr) {
						e->getComponent<Interactible>()->interact(e, dynamic_cast<PlayState*>(Game::Instance()->stateMachine_.currentState())->inventory->getComponent<Inventory>());
						e->delComponent(e->getComponent<ImageRenderer>());
					}
					else std::cout << "Esta entidad no tiene el componegnte Interactible." << std::endl; // DEBUG
				}
			}
		}
	}
	else if (state[inventory_])
	{
		if (event.type == SDL_KEYDOWN && !InventoryOpen) {
			Game::Instance()->getEntityWithComponent<Inventory>()->setActive(!Game::Instance()->getEntityWithComponent<Inventory>()->isActive());
			InventoryOpen = true;
		}
		if (event.type == SDL_KEYUP) {
			InventoryOpen = false;
		}
	}
	else if (state[attack_])
	{
		if (event.type == SDL_KEYDOWN && !(o->getComponent<Character>()->getAttacking())) 
			o->getComponent<Character>()->setAttacking(true);
		
	}
	/*else if (state[interact_]) {

		SDL_Rect playerRect = { o->getPosition().getX(), o->getPosition().getX(), o->getWidth(), o->getHeight() };
		for (Entity* e : *Game::Instance()->stateMachine_.currentState()->getInteractibles()) {
			SDL_Rect intRect = { e->getPosition().getX(), e->getPosition().getX(), e->getWidth(), e->getHeight() };
			if (Collisions::RectRect(&playerRect, &intRect)) {
				if (e->getComponent<Interactible>() != nullptr) {
					e->getComponent<Interactible>()->interact();
				}
			}
		}
	}*/

	else {
		velocity.setY(0);
		direction.setY(0);
	}

	o->setVelocity(velocity);
	o->setDirection(direction);

}
