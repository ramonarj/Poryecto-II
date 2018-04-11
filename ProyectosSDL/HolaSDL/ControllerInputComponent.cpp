#include "ControllerInputComponent.h"
#include "ImageRenderer.h"
#include <iostream>
#include "Camera.h"
#include "Craft.h"


ControllerInputComponent::ControllerInputComponent()
{
	//When you create this component and assign it, it tries to initialise de controller
	initialiseJoysticks();
}


ControllerInputComponent::~ControllerInputComponent()
{
	clean();
}


bool ControllerInputComponent::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			int h = SDL_NumJoysticks();
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			m_joysticks.push_back(joy);
			m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); // add our pair

			std::vector<bool> tempButtons;
			for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
			{
				tempButtons.push_back(false);
			}
			m_buttonStates.push_back(tempButtons);

			if (tempButtons.size() == 14) {
				increment = 1;
				controllerType = false;
			}
			else if (tempButtons.size() == 11) {
				increment = 8;
				controllerType = true;
			}

		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << "joystick(s)";

		

	}
	else
	{
		m_bJoysticksInitialised = false;
	}
	return m_bJoysticksInitialised;
}

void ControllerInputComponent::clean() {
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
		m_bJoysticksInitialised = false;
		m_joystickValues.clear();
		m_buttonStates.clear();
		m_joysticks.clear();
	}
}

int ControllerInputComponent::xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}
	return 0;
}


int ControllerInputComponent::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}

void ControllerInputComponent::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {
	
	if (event.type == SDL_JOYDEVICEREMOVED) {
		o->getComponent<KeyBoardInputComponent>()->setEnabled(true);
		active_ = false;
		clean();
	}
	else if(event.type == SDL_JOYDEVICEADDED) {
		initialiseJoysticks();
		mouseX = 500;
		mouseY = 500;
		o->getComponent<KeyBoardInputComponent>()->setEnabled(false);
		active_ = true;
	}

	if (m_bJoysticksInitialised && active_) {

		Vector2D velocity = o->getVelocity();
		Vector2D direction = o->getDirection();
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		double vel = 7 * Camera::Instance()->getZoom();


		//JOYSTICK IZQUIERDO
		if (event.type == SDL_JOYAXISMOTION) // check the type value
		{
			// left stick move left or right
			if (event.jaxis.axis == 0)
			{
				if (event.jaxis.value > m_joystickDeadZone)		//This value goes from -33000 until 33000
				{
					m_joystickValues[0].first->setX(1);		//joystick izquierdo - derecha
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[0].first->setX(-1);		//joystick izquierdo - izquierda
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
					m_joystickValues[0].first->setY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)	//joystick izquierdo - arriba
				{
					m_joystickValues[0].first->setY(-1);
				}
				else
				{
					m_joystickValues[0].first->setY(0);
				}
			}
			
		}


		//JOYSTICK DERECHO
		if (controllerType) {										//XBOX
			int b = SDL_JoystickGetAxis(m_joysticks[0], 3);
			int a = SDL_JoystickGetAxis(m_joysticks[0], 4);

			if (b > m_joystickDeadZone / 4)		//This value goes from -33000 until 33000
			{
				mouseX += increment;						//joystick derecho - derecha
			}
			else if (b < -m_joystickDeadZone / 4)
			{
				mouseX -= increment;						//joystick derecho - izquierda
			}


			if (a > m_joystickDeadZone / 4)			//joystick derecho - abajo
			{
				mouseY += increment;
			}
			else if (a < -m_joystickDeadZone / 4)	//joystick derecho - arriba
			{
				mouseY -= increment;
			}
		}

		if (!controllerType) {								//PLAY
			

			int b = SDL_JoystickGetAxis(m_joysticks[0], 2);
			int a = SDL_JoystickGetAxis(m_joysticks[0], 5);

			if (b >= SDL_JOYSTICK_AXIS_MAX-2000 || b <= SDL_JOYSTICK_AXIS_MIN+2000 || a >= SDL_JOYSTICK_AXIS_MAX-2000 || a <= SDL_JOYSTICK_AXIS_MIN+2000)
				increment = 5;
			else
				increment = 1;

			if (b > m_joystickDeadZone / 4)		//This value goes from -33000 until 33000
			{
				mouseX += increment;						//joystick derecho - derecha
			}
			else if (b < -m_joystickDeadZone / 4)
			{
				mouseX -= increment;						//joystick derecho - izquierda
			}
			
			
			if (a > m_joystickDeadZone / 4)			//joystick derecho - abajo
			{
				mouseY += increment;
			}
			else if (a < -m_joystickDeadZone / 4)	//joystick derecho - arriba
			{
				mouseY -= increment;
			}

		}

		SDL_WarpMouseGlobal(mouseX, mouseY);





		//BOTONES DEL MANDO		COLOCA EL ESTADO DE ESE BOT�N A ACTIVO AL PULSARLO Y SE QUEDA ASI HASTA QUE SE SUELTA EL BOTON
		if (event.type == SDL_JOYBUTTONDOWN)
		{

			m_buttonStates[0][event.jbutton.button] = true;
			ProcessButton(0, event.jbutton.button);
		}

		if (event.type == SDL_JOYBUTTONUP)
		{
			m_buttonStates[0][event.jbutton.button] = false;
		}



		if (inv == nullptr)
			inv = Game::Instance()->getEntityWithComponent<Inventory>();

		if (inv != nullptr && !inv->isActive()) {
			if (m_joystickValues[0].first->getX() == -1 && !(o->getComponent<Character>()->getAttacking())) {		//ESTO SE PODRIA AGRUPAR COMO CONDICIONE GENERAL YA QUE SI ESTAS ATACANDO TAMPOCO DEBERIAS PODER HACER OTRAS COSAS
				velocity.setX(-vel);
				direction.setX(-1);
			}
			else if (m_joystickValues[0].first->getX() == 1 && !(o->getComponent<Character>()->getAttacking())) {
				velocity.setX(vel);
				direction.setX(1);
			}
			else {
				velocity.setX(0);
				direction.setX(0);
			}
			if (m_joystickValues[0].first->getY() == -1 && !(o->getComponent<Character>()->getAttacking())) {
				velocity.setY(-vel);
				direction.setY(1);
			}
			else if (m_joystickValues[0].first->getY() == 1 && !(o->getComponent<Character>()->getAttacking())) {
				velocity.setY(vel);
				direction.setY(-1);
			}
			else if ((!controllerType && m_buttonStates[0][Square]) || (controllerType && m_buttonStates[0][X])) {		//Interacturar
				SDL_Rect playerRect = { int(o->getPosition().getX()), int(o->getPosition().getY()), int(o->getWidth()), int(o->getHeight()) };
				for (Entity* e : *Game::Instance()->stateMachine_.currentState()->getInteractibles()) {
					SDL_Rect intRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };
					if (Collisions::RectRect(&playerRect, &intRect) && e->isActive()) {
						if (e->getComponent<Interactible>() != nullptr) {
							e->getComponent<Interactible>()->interact(e);
						}
						else std::cout << "Esta entidad no tiene el componente Interactible." << std::endl; // DEBUG
					}
				}
			}

			else if (((!controllerType && m_buttonStates[0][Circle]) || (controllerType && m_buttonStates[0][B])) && (inv->getComponent<Inventory>()->currentWeapon() != nullptr))	//Can only attack if you have an equiped weapon
			{
				if (!(o->getComponent<Character>()->getAttacking())) {
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
			o->setVelocity(Vector2D(0, 0));
		}


		//INVENTARIO, COFRE Y CRAFTEO COMO HAY TANTOS CASOS QUE TENER EN CUENTA SE USAN VARIAS VARIABLES DE CONTROL, MIRAR .h
		if (m_buttonStates[0][Triangle] && !cstOpen && !crftOpen)		//Inventario
		{
			if (/*event.type == SDL_KEYDOWN &&*/ !inventoryPressed) {
				if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
				if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
				if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }
				Game::Instance()->getResourceManager()->getSound("InventoryOpen")->play();
				inv->setActive(!inv->isActive());
				inventoryPressed = true;
				invOpen = !invOpen;
			}
		}
		if (!m_buttonStates[0][Triangle] && !cstOpen && !crftOpen)
		{
			inventoryPressed = false;
		}

		if (m_buttonStates[0][R1] && !invOpen && !crftOpen)		//Abrir cofre
		{
			if (!chestPressed) {
				if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
				if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
				if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }
				inv->setActive(!inv->isActive());
				cst->setActive(!cst->isActive());
				chestPressed = true;
				cstOpen = !cstOpen;
				inv->getComponent<Inventory>()->setChestMode(cstOpen);
				//SOUND 
				Game::Instance()->getResourceManager()->getSound("Inventory")->play();
			}
		}
		if (!m_buttonStates[0][R1] && !invOpen && !crftOpen)
		{
			chestPressed = false;
		}

		if (m_buttonStates[0][R2] && !invOpen && !cstOpen)
		{
			if (!craftPressed) {
				if (cst == nullptr) { cst = Game::Instance()->getEntityWithComponent<Chest>(); }
				if (inv == nullptr) { inv = Game::Instance()->getEntityWithComponent<Inventory>(); }
				if (craft == nullptr) { craft = Game::Instance()->getEntityWithComponent<Craft>(); }
				inv->setActive(!inv->isActive());
				craft->setActive(!craft->isActive());
				craftPressed = true;
				crftOpen = !crftOpen;
				if (!craft->isActive()) { craft->getComponent<Craft>()->restoreObjects(); }
				inv->getComponent<Inventory>()->setCraftMode(crftOpen);
				//SOUND 
				Game::Instance()->getResourceManager()->getSound("Inventory")->play();
			}
		}
		if (!m_buttonStates[0][R2] && !invOpen && !cstOpen)
		{
			craftPressed = false;
		}

		if ((!controllerType && m_buttonStates[0][Select]) || (controllerType && m_buttonStates[0][SelectXB]))
		{
			o->getComponent<KeyBoardInputComponent>()->setEnabled(true);
			Active(false);
			if(!controllerType)
				m_buttonStates[0][Select] = false;
			else
				m_buttonStates[0][SelectXB] = false;
		}
		if ((!controllerType && m_buttonStates[0][L3]) || (controllerType && m_buttonStates[0][left3]))
		{
			Game::Instance()->setFullScreen();
			if (!controllerType)
				m_buttonStates[0][L3] = false;
			else
				m_buttonStates[0][left3] = false;
		}

	}
}

void ControllerInputComponent::ProcessButton(int joy, int buttonNumber) {


	if (buttonNumber == Cross) {
		std::cout << "You pressed the cross" << std::endl;
	}
	else if (buttonNumber == Square) {
		std::cout << "You pressed the Square" << std::endl;
	}
	else if (buttonNumber == Circle) {
		std::cout << "You pressed the Circle" << std::endl;
	}
	else if (buttonNumber == Triangle) {
		std::cout << "You pressed the Triangle" << std::endl;
	}
	else if (buttonNumber == Start) {
		std::cout << "You pressed the Start" << std::endl;
	}
	else if (buttonNumber == Select) {
		std::cout << "You pressed the Select" << std::endl;
	}

}