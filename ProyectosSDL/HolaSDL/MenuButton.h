#pragma once
#include "GameObject.h"
#include "Texture.h"

typedef void CallBackOnClick(Game* juego);
class MenuButton
{
protected:
	Texture* texture;
	SDL_Rect thisRect;
	CallBackOnClick* cbOnClick;

public:

	virtual void render();
	virtual void update();
	virtual bool handleEvent(SDL_Event& e);
	MenuButton();
	MenuButton(Texture* texture, SDL_Rect rect, CallBackOnClick* cbOnClick);
	~MenuButton();
};

