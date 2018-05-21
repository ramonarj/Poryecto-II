#include "BaseControllerInput.h"



BaseControllerInput::BaseControllerInput()
{
	initialiseJoysticks();
}


BaseControllerInput::~BaseControllerInput()
{
	clean();
}

void BaseControllerInput::clean() {
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
		m_bJoysticksInitialised = false;
		for (int i = 0; i < m_joystickValues.size(); i++)
		{
			delete m_joystickValues.at(i).first;
			delete m_joystickValues.at(i).second;
		}
		m_joystickValues.clear();
		m_buttonStates.clear();
		m_joysticks.clear();
	}
}

bool BaseControllerInput::initialiseJoysticks()
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
				//increment = 1;
				controllerType = false;
			}
			else if (tempButtons.size() == 11) {
				//increment = 8;
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

int BaseControllerInput::xvalue(int joy, int stick)
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

int BaseControllerInput::yvalue(int joy, int stick)
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