#include "ControllerInputComponent.h"
#include "ImageRenderer.h"
#include <iostream>
#include "Camera.h"
#include "Craft.h"
#include "CarnePuaj.h"


ControllerInputComponent::ControllerInputComponent() : messageRenderer(nullptr), messageTimer(nullptr) {
	//When you create this component and assign it, it tries to initialise de controller
	initialiseJoysticks();
}


ControllerInputComponent::~ControllerInputComponent()
{
	clean();
}




void ControllerInputComponent::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {
	
	if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
	if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
	if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }

	if (event.type == SDL_JOYDEVICEREMOVED) {
		o->getComponent<KeyBoardInputComponent>()->setEnabled(true);
		active_ = false;
		inv->getComponent<Inventory>()->setActiveController(false);
		cst->getComponent<Chest>()->setActiveController(false);
		craft->getComponent<Craft>()->setActiveController(false);
		clean();
	}
	else if(event.type == SDL_JOYDEVICEADDED) {
		initialiseJoysticks();
		/*mouseX = 500;
		mouseY = 500;*/
		o->getComponent<KeyBoardInputComponent>()->setEnabled(false);
		inv->getComponent<Inventory>()->setActiveController(true);
		cst->getComponent<Chest>()->setActiveController(true);
		craft->getComponent<Craft>()->setActiveController(true);
		active_ = true;
	}

	if (m_bJoysticksInitialised && active_ && !o->getComponent<Player>()->getAwakening() && o->getComponent<Character>()->isAlive()) {	//Aqui le meto la condicion de estar vivo y no despertando

		Vector2D velocity = o->getVelocity();
		Vector2D direction = o->getDirection();
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		double vel = 7 * Camera::Instance()->getZoom();

		if (!timerSet && dirBlock_ != 0) {
			Timer_ = time;
			timerSet = true;
		}

		if (time > Timer_ + 250) {	//1/4 segundo
			timerSet = false;
			dirBlock_ = 0;
		}

		//JOYSTICK IZQUIERDO
		if (event.type == SDL_JOYAXISMOTION) // check the type value
		{
			// left stick move left or right
			if (event.jaxis.axis == 0)
			{
				if (event.jaxis.value > m_joystickDeadZone)		//This value goes from -33000 until 33000
				{
					if (dirBlock_ != 2 && dirBlock_ != 3 && dirBlock_ != 4) {
						m_joystickValues[0].first->setX(1);		//joystick izquierdo - derecha
						//dirBlock_ = 0;
					}
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					if (dirBlock_ != 7 && dirBlock_ != 8 && dirBlock_ != 6) {
						m_joystickValues[0].first->setX(-1);		//joystick izquierdo - izquierda
						//dirBlock_ = 0;
					}
				}
				else
				{
					m_joystickValues[0].first->setX(0);
				}
			}
			// left stick move up or down
			if (event.jaxis.axis == 1)
			{
				if (event.jaxis.value > m_joystickDeadZone)			//joystick izquierdo - abajo
				{
					if (dirBlock_ != 4 && dirBlock_ != 5 && dirBlock_ != 6) {
						m_joystickValues[0].first->setY(1);
						//dirBlock_ = 0;
					}
				}
				else if (event.jaxis.value < -m_joystickDeadZone)	//joystick izquierdo - arriba
				{
					if (dirBlock_ != 8 && dirBlock_ != 1 && dirBlock_ != 2) {
						m_joystickValues[0].first->setY(-1);
						//dirBlock_ = 0;
					}
				}
				else
				{
					m_joystickValues[0].first->setY(0);
				}
			}	
		}

		//JOYSTICK DERECHO
		int a;	//vertical
		int b;	//horizontal

		//if (controllerType) {										//XBOX
		//	b = SDL_JoystickGetAxis(m_joysticks[0], 3);
		//	a = SDL_JoystickGetAxis(m_joysticks[0], 4);
		//}
		//else if (!controllerType) {								//PLAY
		//	b = SDL_JoystickGetAxis(m_joysticks[0], 2);
		//	a = SDL_JoystickGetAxis(m_joysticks[0], 5);
		//}

		a = SDL_JoystickGetAxis(m_joysticks[0], 1);	//EJE VERTICAL
		b = SDL_JoystickGetAxis(m_joysticks[0], 0); //EJE HORIZONTAL


		//izquierdo derecha
		if (b > m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			if(interfaceActive==1)
				inv->getComponent<Inventory>()->moveMarkSlot(2);						
			else if (interfaceActive == 2) {
				cst->getComponent<Chest>()->moveMarkSlot(2);
			}
			else if (interfaceActive == 3) {
				craft->getComponent<Craft>()->moveMarkSlot(2);		//COMENTADOS POR AHORA
			}
		}
		//izquierdo izquierda
		else if (b < -m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			if (interfaceActive == 1)
				inv->getComponent<Inventory>()->moveMarkSlot(4);
			else if (interfaceActive == 2) {
				cst->getComponent<Chest>()->moveMarkSlot(4);
			}
			else if (interfaceActive == 3) {
				craft->getComponent<Craft>()->moveMarkSlot(4);		//COMENTADOS POR AHORA
			}
		}
		else if((b > -m_joystickDeadZone && b < m_joystickDeadZone)&&(a > -m_joystickDeadZone && a < m_joystickDeadZone))
		{
			joystickMoved = false;
		}


		//Derecho abajo
		if (a > m_joystickDeadZone && !joystickMoved)			
		{
			joystickMoved = true;
			if (interfaceActive == 1)
				inv->getComponent<Inventory>()->moveMarkSlot(3);
			else if (interfaceActive == 2) {
				cst->getComponent<Chest>()->moveMarkSlot(3);
			}
			else if (interfaceActive == 3) {
				craft->getComponent<Craft>()->moveMarkSlot(3);
			}
		}

		else if (a < -m_joystickDeadZone && !joystickMoved)	//joystick derecho - arriba
		{
			joystickMoved = true;
			if (interfaceActive == 1)
				inv->getComponent<Inventory>()->moveMarkSlot(1);
			else if (interfaceActive == 2) {
				cst->getComponent<Chest>()->moveMarkSlot(1);
			}
			else if (interfaceActive == 3) {
				craft->getComponent<Craft>()->moveMarkSlot(1);
			}
		}
		else if ((b > -m_joystickDeadZone && b < m_joystickDeadZone) && (a > -m_joystickDeadZone && a < m_joystickDeadZone))
		{
			joystickMoved = false;
		}
		

		//BOTONES DEL MANDO		COLOCA EL ESTADO DE ESE BOT�N A ACTIVO AL PULSARLO Y SE QUEDA ASI HASTA QUE SE SUELTA EL BOTON
		if (event.type == SDL_JOYBUTTONDOWN)
		{
			m_buttonStates[0][event.jbutton.button] = true;
		}

		if (event.type == SDL_JOYBUTTONUP)
		{
			m_buttonStates[0][event.jbutton.button] = false;
		}

		alphaFade_ = Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getAlphaFade();
		
		if (inv == nullptr)
			inv = Game::Instance()->getEntityWithComponent<Inventory>();

		if (!o->getComponent<Player>()->getAwakening() && o->getComponent<Character>()->isAlive() && alphaFade_==0) {

			if (inv != nullptr) {
				if (m_joystickValues[0].first->getX() == -1 && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive()) {		//ESTO SE PODRIA AGRUPAR COMO CONDICIONE GENERAL YA QUE SI ESTAS ATACANDO TAMPOCO DEBERIAS PODER HACER OTRAS COSAS
					velocity.setX(-vel);
					direction.setX(-1);
				}
				else if (m_joystickValues[0].first->getX() == 1 && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive()) {
					velocity.setX(vel);
					direction.setX(1);
				}
				else {
					velocity.setX(0);
					direction.setX(0);
				}
				if (m_joystickValues[0].first->getY() == -1 && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive()) {
					velocity.setY(-vel);
					direction.setY(1);
				}
				else if (m_joystickValues[0].first->getY() == 1 && !(o->getComponent<Character>()->getAttacking()) && !o->getIsReading() && !inv->isActive()) {
					velocity.setY(vel);
					direction.setY(-1);
				}
				else if (((!controllerType && m_buttonStates[0][Square]) || (controllerType && m_buttonStates[0][X])) && !interactButtonPressedSquare) {		//INTERACTUAR
					SDL_Rect playerRect = { int(o->getPosition().getX()), int(o->getPosition().getY()), int(o->getWidth()), int(o->getHeight()) };
					bool entityFound = false;
					int i = 0;
					list<Entity*>::const_iterator it = (Game::Instance()->stateMachine_.currentState()->getInteractibles()->begin());
					while (it != (Game::Instance()->stateMachine_.currentState()->getInteractibles()->end()) && !entityFound) {
						SDL_Rect intRect;
						if ((*it)->getComponent<CarnePuaj>() != nullptr)
							intRect = { int((*it)->getPosition().getX() - (*it)->getWidth() / 2), int((*it)->getPosition().getY() - (*it)->getHeight() / 2), int(2 * (*it)->getWidth()), int(2 * (*it)->getHeight()) };
						else
							intRect = { int((*it)->getPosition().getX()), int((*it)->getPosition().getY()), int((*it)->getWidth()), int((*it)->getHeight()) };
						if (Collisions::RectRect(&playerRect, &intRect) && (*it)->isActive()) {

							//AQUI SERIA CUANDO SE REGISTRA EL COFRE O LA MESA DE CRAFTEO Y SEGÚN CUAL METER AQUI LO QUE SE REALIZA CUANDO SE PULSA EL BOTON DEL COFRE/INVENTARIO

							if ((*it)->getName() == "CraftingTable" && !crftOpen && !invOpen) {	//Si lo que interactuamos tiene componente de crafteo

								inv->setActive(!inv->isActive());
								craft->setActive(!craft->isActive());
								crftOpen = !crftOpen;
								if (!craft->isActive()) { craft->getComponent<Craft>()->restoreObjects(); }
								inv->getComponent<Inventory>()->setCraftMode(crftOpen);
								//SOUND 
								Game::Instance()->getResourceManager()->getSound("InventorySound")->play();

								if (interfaceActive == 0) interfaceActive = 1;			//Interfaz del inventario
								else interfaceActive = 0;

								inv->getComponent<Inventory>()->setRenderMark(true);
								craft->getComponent<Craft>()->setRenderMark(false);
								interactButtonPressedSquare = true;
								entityFound = true;
							}
							else if ((*it)->getName() == "Chest" && !cstOpen && !invOpen) {

								inv->setActive(!inv->isActive());
								cst->setActive(!cst->isActive());
								chestPressed = true;
								cstOpen = !cstOpen;
								inv->getComponent<Inventory>()->setChestMode(cstOpen);
								//SOUND 
								Game::Instance()->getResourceManager()->getSound("ChestSound")->play();

								if (interfaceActive == 0) interfaceActive = 1;			//Interfaz del inventario
								else interfaceActive = 0;

								inv->getComponent<Inventory>()->setRenderMark(true);
								cst->getComponent<Chest>()->setRenderMark(false);

								interactButtonPressedSquare = true;
								entityFound = true;

							}
							else if (!cstOpen && !invOpen && !crftOpen) {
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
								interactButtonPressedSquare = true;
								entityFound = true;
							}
							else {
								++it;
							}
						}
						else
							++it;
					}
				}
				else if (((!controllerType && !m_buttonStates[0][Square]) || (controllerType && !m_buttonStates[0][X])) && interactButtonPressedSquare) {
					interactButtonPressedSquare = false;
				}

				else if (((!controllerType && m_buttonStates[0][Circle]) || (controllerType && m_buttonStates[0][B])) && !interactButtonPressedCircle && !o->getIsReading())	//Can only attack if you have an equiped weapon
				{
					if (inv->getComponent<Inventory>()->currentWeapon() != nullptr && !invOpen && !cstOpen && !crftOpen) {
						if (!(o->getComponent<Character>()->getAttacking()) && !(o->getComponent<Player>()->getCoolDown())) {
							o->getComponent<Player>()->setWeaponId(inv->getComponent<Inventory>()->equiped->getComponent<Weapon>()->getTypeStr());
							o->getComponent<Character>()->setAttacking(true);
							o->getComponent<Player>()->startCoolDown();
							std::cout << o->getComponent<Player>()->getWeaponId() << std::endl;
						}
					}
				}
				else {
					velocity.setY(0);
					direction.setY(0);
				}
				o->setVelocity(velocity);
				o->setDirection(direction);
			}
		}
		else {
			o->setVelocity(Vector2D(0, 0));
		}

		//INVENTARIO, COFRE Y CRAFTEO COMO HAY TANTOS CASOS QUE TENER EN CUENTA SE USAN VARIAS VARIABLES DE CONTROL, MIRAR .h
		if (m_buttonStates[0][Triangle] && !cstOpen && !crftOpen && !o->getIsReading())		//Inventario
		{
			if (!inventoryPressed) {
				Game::Instance()->getResourceManager()->getSound("InventorySound")->play();
				inv->setActive(!inv->isActive());
				inv->getComponent<Inventory>()->setSelectedSlot(0);
				inventoryPressed = true;
				invOpen = !invOpen;

				if(interfaceActive==0) interfaceActive = 1;			//Interfaz del inventario
				else interfaceActive = 0;

				inv->getComponent<Inventory>()->setRenderMark(true);
			}
		}
		if (!m_buttonStates[0][Triangle] && !cstOpen && !crftOpen)
		{
			inventoryPressed = false;
		}
		


		///////////////////////////////////////////////////////////////////////////////
		////////////////////INTERACCIONES DENTRO DE LOS MENUS//////////////////////////
		///////////////////////////////////////////////////////////////////////////////


		//ESTAR SOLO EN EL INVENTARIO

		if (((!controllerType && m_buttonStates[0][Cross]) || (controllerType && m_buttonStates[0][A])) && invOpen && !cstOpen && !crftOpen && !interactButtonPressedCross)	
		{
			inv->getComponent<Inventory>()->activeItem();
			interactButtonPressedCross = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Cross]) || (controllerType && !m_buttonStates[0][A])) && invOpen && !cstOpen && !crftOpen && interactButtonPressedCross) {
			interactButtonPressedCross = false;
		}


		//ESTAR EN EL COFRE

		//Cambiar de interfaz
		if (m_buttonStates[0][L1] && !invOpen && cstOpen && !crftOpen && !interactButtonPressedLeftShoulder)	
		{
			if (interfaceActive == 1) {
				interfaceActive = 2;
				inv->getComponent<Inventory>()->setRenderMark(false);
				cst->getComponent<Chest>()->setRenderMark(true);
			}
			else {
				interfaceActive = 1;
				inv->getComponent<Inventory>()->setRenderMark(true);
				cst->getComponent<Chest>()->setRenderMark(false);
			}
			interactButtonPressedLeftShoulder = true;
		}
		else if (!m_buttonStates[0][L1] && !invOpen && cstOpen && !crftOpen && interactButtonPressedLeftShoulder) {
			interactButtonPressedLeftShoulder = false;
		}


		//Activar el objeto si estas en el inventario
		if (((!controllerType && m_buttonStates[0][Cross]) || (controllerType && m_buttonStates[0][A])) && !invOpen && cstOpen && !crftOpen && !interactButtonPressedCross)	
		{
			if (interfaceActive == 1) {
				inv->getComponent<Inventory>()->activeItem();
			}

			interactButtonPressedCross = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Cross]) || (controllerType && !m_buttonStates[0][A])) && !invOpen && cstOpen && !crftOpen && interactButtonPressedCross) {
			interactButtonPressedCross = false;
		}


		if (((!controllerType && m_buttonStates[0][Circle]) || (controllerType && m_buttonStates[0][B])) && !invOpen && cstOpen && !crftOpen && !interactButtonPressedCircle)
		{
			inv->setActive(!inv->isActive());
			cst->setActive(!cst->isActive());
			cstOpen = !cstOpen;
			inv->getComponent<Inventory>()->setChestMode(cstOpen);
			//SOUND
			//Game::Instance()->getResourceManager()->getSound("Inventory")->play();

			if (interfaceActive == 0) interfaceActive = 1;			//Interfaz del inventario
			else interfaceActive = 0;

			inv->getComponent<Inventory>()->setRenderMark(true);
			cst->getComponent<Chest>()->setRenderMark(false);
			cst->getComponent<Chest>()->setSelectedSlot(0);

			interactButtonPressedCircle = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Circle]) || (controllerType && !m_buttonStates[0][B])) && interactButtonPressedCircle) {
			interactButtonPressedCircle = false;
		}


		//Coger del inventario para guardarlo en el cofre
		if (((!controllerType && m_buttonStates[0][Square]) || (controllerType && m_buttonStates[0][X])) && !invOpen && cstOpen && !crftOpen && !interactButtonPressedSquare)
		{
			if (interfaceActive == 1) {
				inv->getComponent<Inventory>()->moveItem();
			}
			else if (interfaceActive == 2) {
				cst->getComponent<Chest>()->moveItem();
			}

			interactButtonPressedSquare = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Square]) || (controllerType && !m_buttonStates[0][X])) && !invOpen && cstOpen && !crftOpen && interactButtonPressedSquare) {
			interactButtonPressedSquare = false;
		}



		//ESTAR EN EL CRAFTEO

		if (m_buttonStates[0][L1] && !invOpen && !cstOpen && crftOpen && !interactButtonPressedLeftShoulder)		//CAMBIO DE INTERFAZ
		{
			if (interfaceActive == 1) {
				interfaceActive = 3;
				inv->getComponent<Inventory>()->setRenderMark(false);
				craft->getComponent<Craft>()->setRenderMark(true);
			}
			else if (interfaceActive == 3 && !craft->getComponent<Craft>()->getCraftButtonSelected() && !craft->getComponent<Craft>()->getRepairButtonSelected()) {
				interfaceActive = 1;
				inv->getComponent<Inventory>()->setRenderMark(true);
				craft->getComponent<Craft>()->setRenderMark(false);
			}
			interactButtonPressedLeftShoulder = true;
		}
		else if (!m_buttonStates[0][L1] && !invOpen && !cstOpen && crftOpen && interactButtonPressedLeftShoulder) {
			interactButtonPressedLeftShoulder = false;
		}


		//Activar el objeto si estas en el inventario
		if (((!controllerType && m_buttonStates[0][Cross]) || (controllerType && m_buttonStates[0][A])) && !invOpen && !cstOpen && crftOpen && !interactButtonPressedCross)
		{
			if (interfaceActive == 1) {
				inv->getComponent<Inventory>()->activeItem();
			}
			if (interfaceActive == 3) {
				craft->getComponent<Craft>()->tryCraftingRepair();	//ESTE METODO HABRA QUE CAMBIARLO YA QUE CONTROLAS CRAFTEO Y REPARACIÓN
			}

			interactButtonPressedCross = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Cross]) || (controllerType && !m_buttonStates[0][A])) && !invOpen && !cstOpen && crftOpen && interactButtonPressedCross) {
			interactButtonPressedCross = false;
		}


		//Cancelar crafteo/reparacion
		if (((!controllerType && m_buttonStates[0][Circle]) || (controllerType && m_buttonStates[0][B])) && !invOpen && !cstOpen && crftOpen && !interactButtonPressedCircle)
		{
			if (craft->getComponent<Craft>()->getCraftButtonSelected() || craft->getComponent<Craft>()->getRepairButtonSelected()) {
					craft->getComponent<Craft>()->retireBlock();
			}
			else {
				inv->setActive(!inv->isActive());
				craft->setActive(!craft->isActive());
				//craftPressed = true;
				crftOpen = !crftOpen;
				if (!craft->isActive()) { craft->getComponent<Craft>()->restoreObjects(); }
				inv->getComponent<Inventory>()->setCraftMode(crftOpen);
				//SOUND 
				Game::Instance()->getResourceManager()->getSound("InventorySound")->play();

				if (interfaceActive == 0) interfaceActive = 1;			//Interfaz del inventario
				else interfaceActive = 0;

				inv->getComponent<Inventory>()->setRenderMark(true);
				craft->getComponent<Craft>()->setRenderMark(false);
			}

			interactButtonPressedCircle = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Circle]) || (controllerType && !m_buttonStates[0][B])) && !invOpen && !cstOpen && crftOpen && interactButtonPressedCircle) {
			interactButtonPressedCircle = false;
		}

		//Coger del inventario arma y material y devolverlo
		if (((!controllerType && m_buttonStates[0][Square]) || (controllerType && m_buttonStates[0][X])) && !invOpen && !cstOpen && crftOpen && !interactButtonPressedSquare)
		{
			if (interfaceActive == 1) {
				inv->getComponent<Inventory>()->setToRepair();
				if (craft->getComponent<Craft>()->checkRepair()) {
					interfaceActive = 3;
					inv->getComponent<Inventory>()->setRenderMark(false);
					craft->getComponent<Craft>()->setRenderMark(true);
				}
			}
			else if (interfaceActive == 3) {
				craft->getComponent<Craft>()->returnToInv();
			}

			interactButtonPressedSquare = true;
		}
		else if (((!controllerType && !m_buttonStates[0][Square]) || (controllerType && !m_buttonStates[0][X])) && !invOpen && !cstOpen && crftOpen && interactButtonPressedSquare) {
			interactButtonPressedSquare = false;
		}


		//SELECT PARA VOLVER A TECLADO Y RATON

		if ((!controllerType && m_buttonStates[0][Select]) || (controllerType && m_buttonStates[0][SelectXB]))		
		{
			o->getComponent<KeyBoardInputComponent>()->setEnabled(true);
			Active(false);
			if(!controllerType)
				m_buttonStates[0][Select] = false;
			else
				m_buttonStates[0][SelectXB] = false;	
		}

		if ((!controllerType && m_buttonStates[0][L3]) || (controllerType && m_buttonStates[0][left3]))		//PANTALLA COMPLETA
		{
			Game::Instance()->setFullScreen();
			if (!controllerType)
				m_buttonStates[0][L3] = false;
			else
				m_buttonStates[0][left3] = false;
		}
	}
}