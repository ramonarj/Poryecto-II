#pragma once

#include "BaseControllerInput.h"



class ControllerInputComponent :
	public BaseControllerInput
{
public:
	ControllerInputComponent();
	virtual ~ControllerInputComponent();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
	
	//void ProcessButton(int joy, int buttonNumber);
	void Active(bool value) { active_ = value;};
	void setDirBlock(int a) { dirBlock_ = a; };

private:	

	//VARIABLE PARA EVITAR EL PARPADEO DEL INVENTARIO Y PARA CUADRAR QUE SE ABRAN LAS 
	//INTERFACES CORRECTAS SIN QUE SE ABRAN Y CIERREN DE FORMAS DESIGUALES
	bool inventoryPressed = false, chestPressed = false, craftPressed = false, invOpen = false, cstOpen = false, crftOpen = false;
	Entity* inv = nullptr;
	Entity* cst = nullptr;
	Entity* craft = nullptr;
	bool chestOpen() { return cstOpen; };
	bool InventoryOpen() { return invOpen; };
	bool craftOpen() { return craft; };

	bool joystickMoved = false;

	bool interactButtonPressedCross = false;
	bool interactButtonPressedSquare = false;
	bool interactButtonPressedCircle = false;
	bool interactButtonPressedLeftShoulder = false;

	int interfaceActive = 0;	//0=ninguna abierta, 1=inventario, 2=cofre, 3=crafteo
									
	//MessageRenderer
	MessageRenderer* messageRenderer;
	MessageTimer* messageTimer;

	////*MOUSE*
	//int mouseX = 0; int mouseY = 0;
	//int increment = 5;

	//Knockback easy
	Uint32 Timer_ = 0;
	bool timerSet = false;
	int dirBlock_ = 0;
	Uint8 alphaFade_;
};

