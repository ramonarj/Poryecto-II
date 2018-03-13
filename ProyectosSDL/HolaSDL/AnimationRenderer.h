#pragma once
#include "Component.h"
#include "Entity.h"
#include "Game.h"

class AnimationRenderer :
	public Component
{
public:
	AnimationRenderer(Texture* image, Uint32 movementFrames, Uint32 attackMovementFrames, Uint32 cooldown, bool character, bool direccionable);
	virtual ~AnimationRenderer();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};

private:
	Texture *image_;
	Uint32 movementFrames_, movements_ = 4, frame_ = 0, idleFrame_ = 0, actualTime_ = 0, cooldown_, cooldownIddle_ = cooldown_*5;
	Uint32 attackMovementFrames_, attackFrames_ = 14;
	Vector2D lastDir;
	int dir(Entity* o);
	int dirIddle(Entity* o);
	bool character, direccionable;
};

