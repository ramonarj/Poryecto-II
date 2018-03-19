#include "KeyBoardInputComponent.h"
#include "ImageRenderer.h"
#include <iostream>
#include "Camera.h"


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
	double vel = 3 * Camera::Instance()->getZoom();

	if (inv != nullptr && !inv->isActive()) {
		if (state[left_] && !(o->getComponent<Character>()->getAttacking())) {		//ESTO SE PODRIA AGRUPAR COMO CONDICIONE GENERAL YA QUE SI ESTAS ATACANDO TAMPOCO DEBERIAS PODER HACER OTRAS COSAS
			velocity.setX(-vel);
			direction.setX(-1);
		}
		else if (state[right_] && !(o->getComponent<Character>()->getAttacking())) {
			velocity.setX(vel);
			direction.setX(1);
		}
		else {
			velocity.setX(0);
			direction.setX(0);
		}
		if (state[up_] && !(o->getComponent<Character>()->getAttacking())) {
			velocity.setY(-vel);
			direction.setY(1);
		}
		else if (state[down_] && !(o->getComponent<Character>()->getAttacking())) {
			velocity.setY(vel);
			direction.setY(-1);
		}
		else if (state[interact_]) {
			if (event.type == SDL_KEYDOWN) {
				SDL_Rect playerRect = { int(o->getPosition().getX()), int(o->getPosition().getX()), int(o->getWidth()), int(o->getHeight()) };
				for (Entity* e : *Game::Instance()->stateMachine_.currentState()->getInteractibles()) {
					SDL_Rect intRect = { int(e->getPosition().getX()), int(e->getPosition().getX()), int(e->getWidth()), int(e->getHeight()) };
					if (Collisions::RectRect(&playerRect, &intRect) && e->isActive()) {
						if (e->getComponent<Interactible>() != nullptr) {
							e->getComponent<Interactible>()->interact(e, dynamic_cast<PlayState*>(Game::Instance()->stateMachine_.currentState())->inventory->getComponent<Inventory>());
						}
						else std::cout << "Esta entidad no tiene el componente Interactible." << std::endl; // DEBUG
					}
				}
			}
		}

		else if (state[attack_] && (inv->getComponent<Inventory>()->currentWeapon() != nullptr))	//Can only attack if you have an equiped weapon
		{
			if (event.type == SDL_KEYDOWN && !(o->getComponent<Character>()->getAttacking())) {
				o->getComponent<Player>()->setWeaponId(inv->getComponent<Inventory>()->equiped->getComponent<Weapon>()->getTypeStr());
				o->getComponent<Character>()->setAttacking(true);
				std::cout << o->getComponent<Player>()->getWeaponId() << std::endl;
			}
		}
		else {
			velocity.setY(0);
			direction.setY(0);
		}

		o->setVelocity(velocity);
		o->setDirection(direction);
	}
	else {
		o->setVelocity(Vector2D(0,0));
	}

	if (state[inventory_])
	{
		if (event.type == SDL_KEYDOWN && !inventoryPressed) {
			if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
			inv->setActive(!inv->isActive());
			inventoryPressed = true;
		}
	}
	if (!state[inventory_])
	{
		inventoryPressed = false;
	}

}

