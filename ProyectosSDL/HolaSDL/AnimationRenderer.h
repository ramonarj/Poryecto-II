#pragma once
#include "Component.h"
#include "Entity.h"
#include "Game.h"

class AnimationRenderer :
	public Component
{
public:
	AnimationRenderer(Texture* image, Uint32 movementFrames, bool character);
	virtual ~AnimationRenderer();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};

private:
	Texture* image_, *idleImage_ = nullptr;
	Uint32 movementFrames, movements = 4, frame = 0, idleFrame = 0, actualTime = 0, cooldown = 80;
	Vector2D lastDir;
	int dir(Entity* o);
	bool character;
};

