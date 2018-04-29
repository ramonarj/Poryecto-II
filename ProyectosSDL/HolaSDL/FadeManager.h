#pragma once
#include "Component.h"
class FadeManager :
	public Component
{
public:
	FadeManager();
	virtual ~FadeManager();
	virtual void render(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);

private:
	Texture * fade_ = nullptr;
	Entity* player_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};

