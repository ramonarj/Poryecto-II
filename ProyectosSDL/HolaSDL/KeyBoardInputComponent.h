#pragma once

#include "Component.h"
#include "Game.h"
#include "Entity.h"
#include "Collisions.h"
#include <iostream>
#include "MessageRenderer.h"
#include "MessageTimer.h"

class KeyBoardInputComponent :
	public Component
{
public:
	KeyBoardInputComponent();		
	KeyBoardInputComponent(SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down, SDL_Scancode interact, SDL_Scancode attack, 
		SDL_Scancode inventory, SDL_Scancode chest, SDL_Scancode pause, SDL_Scancode enter, SDL_Scancode crafteo, SDL_Scancode SwitchController, 
		SDL_Scancode saveGame, SDL_Scancode loadGame);
	virtual ~KeyBoardInputComponent();
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);

	void setDirBlock(int a) { dirBlock_ = a; };
	void interactDeadRegister(){ 
		if(lastInteractible!=nullptr)
			lastInteractible->interact((thisEntity_));
	}
	void switchOffInv();

	bool chestOpen() { return cstOpen; };
	bool InventoryOpen() { return invOpen; };
	bool craftOpen() { return craft; };

private:
	SDL_Scancode left_;
	SDL_Scancode right_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode interact_;
	SDL_Scancode attack_;
	SDL_Keycode inventory_;
	SDL_Keycode chest_;
	SDL_Keycode craft_;
	SDL_Scancode pause_;
	SDL_Scancode enter_;
	SDL_Scancode switchController_;
	SDL_Scancode saveGame_;
	SDL_Scancode loadGame_;

	//VARIABLE PARA EVITAR EL PARPADEO DEL INVENTARIO Y PARA CUADRAR QUE SE ABRAN LAS 
	//INTERFACES CORRECTAS SIN QUE SE ABRAN Y CIERREN DE FORMAS DESIGUALES
	bool inventoryPressed = false, chestPressed = false, craftPressed = false, invOpen = false, cstOpen = false, crftOpen = false;
	Entity* inv = nullptr;
	Entity* cst = nullptr;
	Entity* craft = nullptr;
	

	//*MOUSE*
	int mouseX=0; int mouseY = 0;

	//Knockback easy
	Uint32 Timer_ = 0;
	bool timerSet = false;
	int dirBlock_ = 0;

	//MessageRenderer
	MessageRenderer* messageRenderer;
	MessageTimer* messageTimer;

	//Alpha del fade para saber si el personaje se puede mover o no
	Uint8 alphaFade_;
	Interactible* lastInteractible = nullptr;
	Entity* thisEntity_ = nullptr;

};

