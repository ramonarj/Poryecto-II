#pragma once
#include "Component.h"
#include "Game.h"
#include "Entity.h"
#include "Collisions.h"
#include <iostream>

//Button enum for PS4 controller
enum controller_buttons { Square, Cross, Circle, Triangle, L1, R1, L2, R2, Select, Start, L3, R3, HomeButton, Panel };

class ControllerInputComponent :
	public Component
{
public:
	ControllerInputComponent();
	virtual ~ControllerInputComponent();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void initialiseJoysticks();
	void clean();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }
	bool getButtonState(int joy, int buttonNumber) { return m_buttonStates[joy][buttonNumber]; }		//Devuelve el estado concreto de un botón (pulsado o no)

	void ProcessButton(int joy, int buttonNumber);

private:
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;		//ARRAY PARA LOS BOTONES
	bool m_bJoysticksInitialised;
	const int m_joystickDeadZone = 10000;

	//VARIABLE PARA EVITAR EL PARPADEO DEL INVENTARIO Y PARA CUADRAR QUE SE ABRAN LAS 
	//INTERFACES CORRECTAS SIN QUE SE ABRAN Y CIERREN DE FORMAS DESIGUALES
	bool inventoryPressed = false, chestPressed = false, craftPressed = false, invOpen = false, cstOpen = false, crftOpen = false;
	Entity* inv = nullptr;
	Entity* cst = nullptr;
	Entity* craft = nullptr;
	bool chestOpen() { return cstOpen; };
	bool InventoryOpen() { return invOpen; };
	bool craftOpen() { return craft; };
};

