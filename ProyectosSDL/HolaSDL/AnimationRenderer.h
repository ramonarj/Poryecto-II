#pragma once
#include "Component.h"
#include "Entity.h"

class AnimationRenderer :
	public Component
{
public:
	AnimationRenderer(Texture* image, Uint32 movementFrames);
	virtual ~AnimationRenderer();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};
	
private:
	Texture* image_;
	Uint32 movementFrames, movements = 4;
	int dir(Entity* o);
};

