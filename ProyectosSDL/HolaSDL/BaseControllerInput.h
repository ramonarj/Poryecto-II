#pragma once
#ifndef BASECONTROLLERINPUT_H
#define BASECONTROLLERINPUT_H

#include "Component.h"
#include "Entity.h"
#include <iostream>
#include "Collisions.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"

enum controller_buttons { Square, Cross, Circle, Triangle, L1, R1, L2, R2, Select, Start, L3, R3, HomeButton, Panel };
enum xbox_controller_buttons { A, B, X, Y, left1, leftTrigger, SelectXB, StartXB, left3, right1, rightTrigger, right3, XboxButton };

class BaseControllerInput : public Component
{
public:
	BaseControllerInput();
	virtual ~BaseControllerInput();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};

	virtual bool initialiseJoysticks();
	void clean();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }
	bool getActive() { return active_; };
	bool getButtonState(int joy, int buttonNumber) { return m_buttonStates[joy][buttonNumber]; }

protected:
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	bool active_ = false;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;		//ARRAY PARA LOS BOTONES
	bool m_bJoysticksInitialised;
	const int m_joystickDeadZone = 15000;

	bool controllerType = false;	//FALSE Play4   //   TRUE XBOX
	bool joystickMoved = false;

	bool interactButtonPressed = false;
};

#endif