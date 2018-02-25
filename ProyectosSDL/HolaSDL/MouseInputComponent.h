#pragma once
#include "InputComponent.h"

enum mouse_buttons { LEFT, MIDDLE, RIGHT };

class MouseInputComponent :
	public InputComponent
{
public:
	MouseInputComponent();
	virtual ~MouseInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }	//Return the active state of the button required
	Vector2D* getMousePosition() { return m_mousePosition; }	//Return the mouse position

private:
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition = new Vector2D(0, 0);
};

