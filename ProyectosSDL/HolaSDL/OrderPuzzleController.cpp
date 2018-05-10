#include "OrderPuzzleController.h"



OrderPuzzleController::OrderPuzzleController()
{
	if (m_bJoysticksInitialised)
		active_ = true;
}


OrderPuzzleController::~OrderPuzzleController()
{
}

void OrderPuzzleController::handleInput(Entity * o, Uint32 time, const SDL_Event & event)
{

	if (puzll_ == nullptr)
		puzll_ = Game::Instance()->getEntityWithComponent<OrderPuzzleComponent>()->getComponent<OrderPuzzleComponent>();

	if (event.type == SDL_JOYDEVICEREMOVED) {
		active_ = false;
		clean();
	}
	else if (event.type == SDL_JOYDEVICEADDED) {
		initialiseJoysticks();
		active_ = true;
	}

	if (m_bJoysticksInitialised && active_) {
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

		int a;	//vertical
		int b;	//horizontal

		a = SDL_JoystickGetAxis(m_joysticks[0], 1);	//EJE VERTICAL
		b = SDL_JoystickGetAxis(m_joysticks[0], 0); //EJE HORIZONTAL


													//izquierdo derecha
		if (b > m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			puzll_->moveMarkSlot(2);
		}
		//izquierdo izquierda
		else if (b < -m_joystickDeadZone && !joystickMoved)
		{
			joystickMoved = true;
			puzll_->moveMarkSlot(4);
		}
		else if ((b > -m_joystickDeadZone && b < m_joystickDeadZone) && (a > -m_joystickDeadZone && a < m_joystickDeadZone))
		{
			joystickMoved = false;
		}


		if (event.type == SDL_JOYBUTTONDOWN)
		{
			m_buttonStates[0][event.jbutton.button] = true;
		}

		if (event.type == SDL_JOYBUTTONUP)
		{
			m_buttonStates[0][event.jbutton.button] = false;
		}


		if (((!controllerType && m_buttonStates[0][Cross]) || (controllerType && m_buttonStates[0][A])) && !interactButtonPressed) {
			puzll_->clickMark();
			interactButtonPressed = !interactButtonPressed;
		}
		else if (((!controllerType && !m_buttonStates[0][Cross]) || (controllerType && !m_buttonStates[0][A])) && interactButtonPressed) {
			interactButtonPressed = false;
		}
		if (((!controllerType && m_buttonStates[0][Square]) || (controllerType && m_buttonStates[0][X])) && !interactButtonPressed) {
			Game::Instance()->getStateMachine()->changeState(PlayState::Instance());
			interactButtonPressed = !interactButtonPressed;
		}
	}

}
