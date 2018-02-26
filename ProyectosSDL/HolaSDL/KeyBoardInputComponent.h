#pragma once
#include "InputComponent.h"
class KeyBoardInputComponent :
	public InputComponent
{
public:
	KeyBoardInputComponent();
	KeyBoardInputComponent(SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down, SDL_Scancode interact, SDL_Scancode attack, SDL_Scancode inventory, SDL_Scancode pause, SDL_Scancode enter);
	virtual ~KeyBoardInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);

private:
	SDL_Scancode left_;
	SDL_Scancode right_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode interact_;
	SDL_Scancode attack_;
	SDL_Scancode inventory_;
	SDL_Scancode pause_;
	SDL_Scancode enter_;
};

