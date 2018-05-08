#include "KeyBoardInputComponent.h"
#include "ImageRenderer.h"
#include <iostream>
#include "Camera.h"
#include "Craft.h"
#include "PlayState.h"

KeyBoardInputComponent::KeyBoardInputComponent()
{
}

KeyBoardInputComponent::KeyBoardInputComponent(SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down, SDL_Scancode interact, SDL_Scancode attack,
	SDL_Scancode inventory, SDL_Scancode chest, SDL_Scancode pause, SDL_Scancode enter, SDL_Scancode crafteo,
	SDL_Scancode SwitchController, SDL_Scancode saveGame, SDL_Scancode loadGame) :
	left_(left), right_(right), up_(up), down_(down), interact_(interact), attack_(attack), inventory_(inventory), chest_(chest), craft_(crafteo), switchController_(SwitchController),
	pause_(pause), enter_(enter), saveGame_(saveGame), loadGame_(loadGame), inventoryPressed(false), chestPressed(false), messageRenderer(nullptr), messageTimer(nullptr),
	alphaFade_(0)
{
}

KeyBoardInputComponent::~KeyBoardInputComponent()
{
}

void KeyBoardInputComponent::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {
	
	alphaFade_ = Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getAlphaFade();
	if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
	if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }

	Vector2D velocity = o->getVelocity();
	Vector2D direction = o->getDirection();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	double vel = 7 * Camera::Instance()->getZoom();

	if (!o->getComponent<Player>()->getAwakening() && o->getComponent<Character>()->isAlive()){

		if (!timerSet && dirBlock_ != 0) {
			Timer_ = time;
			timerSet = true;
		}

		if (time > Timer_ + 250) {	//1/4 segundo
			timerSet = false;
			dirBlock_ = 0;
		}


		if (inv != nullptr) {
			if (state[saveGame_])
			{
				PlayState::Instance()->setSaveGame(true);
			}
			else if (state[loadGame_])
			{
				PlayState::Instance()->setLoadGame(true);
			}
			if (dirBlock_!=7 && dirBlock_!=8 && dirBlock_!=6 && state[left_] && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive() && alphaFade_ == 0) {		//ESTO SE PODRIA AGRUPAR COMO CONDICIONE GENERAL YA QUE SI ESTAS ATACANDO TAMPOCO DEBERIAS PODER HACER OTRAS COSAS
				velocity.setX(-vel);
				direction.setX(-1);
				dirBlock_ = 0;
			}
			else if (dirBlock_ != 2 && dirBlock_ != 3 && dirBlock_ != 4 && state[right_] && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive() && alphaFade_ == 0) {
				velocity.setX(vel);
				direction.setX(1);
				dirBlock_ = 0;
			}
			else {
				velocity.setX(0);
				direction.setX(0);
			}
			if (dirBlock_ != 8 && dirBlock_ != 1 && dirBlock_ != 2 && state[up_] && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive() && alphaFade_ == 0) {
				velocity.setY(-vel);
				direction.setY(1);
				dirBlock_ = 0;
			}
			else if (dirBlock_ != 4 && dirBlock_ != 5 && dirBlock_ != 6 && state[down_] && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive() && alphaFade_ == 0) {
				velocity.setY(vel);
				direction.setY(-1);
				dirBlock_ = 0;
			}
			else if (state[interact_] && !invOpen) {
				if (event.type == SDL_KEYDOWN) {
					SDL_Rect playerRect = { int(o->getPosition().getX()), int(o->getPosition().getY()), int(o->getWidth()), int(o->getHeight()) };

					bool entityFound = false;
					int i = 0;
					list<Entity*>::const_iterator it = (Game::Instance()->stateMachine_.currentState()->getInteractibles()->begin());
					while (it != (Game::Instance()->stateMachine_.currentState()->getInteractibles()->end()) && !entityFound) {
						SDL_Rect intRect = { int((*it)->getPosition().getX()), int((*it)->getPosition().getY()), int((*it)->getWidth()), int((*it)->getHeight()) };
						if (Collisions::RectRect(&playerRect, &intRect) && (*it)->isActive()) {

							if ((*it)->getName() == "CraftingTable") {	//Si lo que interactuamos tiene componente de crafteo

								inv->setActive(!inv->isActive());
								craft->setActive(!craft->isActive());
								//craftPressed = true;
								crftOpen = !crftOpen;
								if (!craft->isActive()) { craft->getComponent<Craft>()->restoreObjects(); }
								inv->getComponent<Inventory>()->setCraftMode(crftOpen);
								//SOUND 
								Game::Instance()->getResourceManager()->getSound("Inventory")->play();

								inv->getComponent<Inventory>()->setRenderMark(true);
								craft->getComponent<Craft>()->setRenderMark(false);

								entityFound = true;
							}
							else if ((*it)->getName() == "Chest") {

								inv->setActive(!inv->isActive());
								cst->setActive(!cst->isActive());
								chestPressed = true;
								cstOpen = !cstOpen;
								inv->getComponent<Inventory>()->setChestMode(cstOpen);
								//SOUND 
								Game::Instance()->getResourceManager()->getSound("Inventory")->play();

								inv->getComponent<Inventory>()->setRenderMark(true);
								cst->getComponent<Chest>()->setRenderMark(false);

								entityFound = true;
							}
							else {
								if (messageRenderer == nullptr)
									messageRenderer = PlayState::Instance()->getMessageRenderer()->getComponent<MessageRenderer>();
								if (messageTimer == nullptr)
									messageTimer = PlayState::Instance()->getMessageRenderer()->getComponent<MessageTimer>();

								Interactible* inter = (*it)->getComponent<Interactible>();
								inter->interact((*it));
								std::string* intMsg = inter->getInteractMessage();
								if (*intMsg != "") {
									messageRenderer->display(*intMsg);
									messageTimer->start(2);
								}
								entityFound = true;
							}
						}
						else {
							++it;
						}
					}
				}
			}

			else if (state[attack_] && (inv->getComponent<Inventory>()->currentWeapon() != nullptr) && !o->getIsReading())	//Can only attack if you have an equiped weapon && pressing shift
			{
				if (event.type == SDL_KEYDOWN && !(o->getComponent<Character>()->getAttacking()) && !(o->getComponent<Player>()->getCoolDown())) {
					o->getComponent<Player>()->setWeaponId(inv->getComponent<Inventory>()->equiped->getComponent<Weapon>()->getTypeStr());
					o->getComponent<Character>()->setAttacking(true);
					o->getComponent<Player>()->startCoolDown();
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
			o->setVelocity(Vector2D(0, 0));
		}


		//INVENTARIO, COFRE Y CRAFTEO COMO HAY TANTOS CASOS QUE TENER EN CUENTA SE USAN VARIAS VARIABLES DE CONTROL, MIRAR .h
		if (state[inventory_] && !cstOpen && !crftOpen)
		{
			if (event.type == SDL_KEYDOWN && !inventoryPressed && !o->getIsReading()) {
				if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
				if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
				if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }
				Game::Instance()->getResourceManager()->getSound("InventoryOpen")->play();
				inv->setActive(!inv->isActive());
				inventoryPressed = true;
				invOpen = !invOpen;
			}
		}
		if (!state[inventory_] && !cstOpen && !crftOpen)
		{
			inventoryPressed = false;
		}

		if (invOpen || cstOpen || crftOpen)
			Game::Instance()->stateMachine_.currentState()->getCursor()->setActive(true);
		else
			Game::Instance()->stateMachine_.currentState()->getCursor()->setActive(false);

		if (state[switchController_]) {
			if (o->getComponent<ControllerInputComponent>()->joysticksInitialised()) {
				this->setEnabled(false);
				o->getComponent<ControllerInputComponent>()->Active(true);
			}
		}
	}

}

