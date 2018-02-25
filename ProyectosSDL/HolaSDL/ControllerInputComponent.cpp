#include "ControllerInputComponent.h"



ControllerInputComponent::ControllerInputComponent()
{
	//When you create this component and assign it, it tries to initialise de controller
	initialiseJoysticks();
}


ControllerInputComponent::~ControllerInputComponent()
{
}


void ControllerInputComponent::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			
			m_joysticks.push_back(joy);
			m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); // add our pair

			std::vector<bool> tempButtons;
			for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
			{
				tempButtons.push_back(false);
			}
			m_buttonStates.push_back(tempButtons);
			
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << "joystick(s)";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

void ControllerInputComponent::clean() {
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
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
}

void ControllerInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	Vector2D velocity = o->getVelocity();

	//EJES SOBRE EL JOYSTICK IZQUIERDO
	if (event.type == SDL_JOYAXISMOTION) // check the type value
	{
		int whichOne = event.jaxis.which; // get which controller

										  // left stick move left or right
		if (event.jaxis.axis == 0)
		{
			if (event.jaxis.value > m_joystickDeadZone)		//This value goes from -33000 until 33000
			{
				m_joystickValues[whichOne].first->setX(1);		//joystick izquierdo - derecha
			}
			else if (event.jaxis.value < -m_joystickDeadZone)
			{
				m_joystickValues[whichOne].first->setX(-1);		//joystick izquierdo - izquierda
			}
			else
			{
				m_joystickValues[whichOne].first->setX(0);
			}
		}
		// left stick move up or down
		if (event.jaxis.axis == 1)
		{
			if (event.jaxis.value > m_joystickDeadZone)			//joystick izquierdo - abajo
			{
				m_joystickValues[whichOne].first->setY(1);
			}
			else if (event.jaxis.value < -m_joystickDeadZone)	//joystick izquierdo - arriba
			{
				m_joystickValues[whichOne].first->setY(-1);
			}
			else
			{
				m_joystickValues[whichOne].first->setY(0);
			}
		}
		velocity.setX(m_joystickValues[whichOne].first->getX());
		velocity.setY(m_joystickValues[whichOne].first->getY());
	}

	//BOTONES DEL MANDO		COLOCA EL ESTADO DE ESE BOTÓN A ACTIVO AL PULSARLO Y SE QUEDA ASI HASTA QUE SE SUELTA EL BOTON
	if (event.type == SDL_JOYBUTTONDOWN)
	{
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = true;
		ProcessButton(whichOne, event.jbutton.button);
	}

	if (event.type == SDL_JOYBUTTONUP)
	{
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = false;
	}




	o->setVelocity(velocity);

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