#include "MouseInputComponent.h"



MouseInputComponent::MouseInputComponent()
{
}


MouseInputComponent::~MouseInputComponent()
{
}


void MouseInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	Vector2D velocity = o->getVelocity();

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT] = true;
			//We could just want to set the position of the mouse when we click (left click this time
			/*m_mousePosition->setX(event.motion.x);
			m_mousePosition->setY(event.motion.y);*/
		}
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE] = true;
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT] = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			m_mouseButtonStates[LEFT] = false;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_mouseButtonStates[MIDDLE] = false;
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			m_mouseButtonStates[RIGHT] = false;
		}
	}

	if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y == 1) // scroll up
		{
			// Pull up code here!
		}
		else if (event.wheel.y == -1) // scroll down
		{
			// Pull down code here!
		}
	}

	if (event.type == SDL_MOUSEMOTION)			//To refresh the position of the mouse every time the mouse moves
	{
		//m_mousePosition->setX(event.motion.x);
		//m_mousePosition->setY(event.motion.y);
	}

	o->setVelocity(velocity);

}