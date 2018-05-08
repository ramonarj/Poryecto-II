#pragma once

#include "Component.h"

#include "Entity.h" 
#include "Game.h"



class AnimationRenderObject : public Component

{

public:

	AnimationRenderObject();
	AnimationRenderObject(Texture* image, int cooldown, bool chest, bool camera, bool on);
	AnimationRenderObject(Texture* image, int cooldown, bool other, bool on, int numFrames);
	AnimationRenderObject(Texture* image, int cooldown, bool on, int numFrames, bool life);

	virtual ~AnimationRenderObject();

	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};

	void setCoolDown(int i) { cooldown_ = i; };
	int getCoolDown() { return cooldown_; };

private:

	Texture * image_;

	bool chest_ = false;
	bool camera_ = false;
	bool on_ = false;
	bool other_ = false;
	bool way_ = true;
	bool life_ = false;

	int numFrames_ = -1;

	int frame_ = -1;
	int orientation_ = -1;
	int cooldown_ = 0;

	int lastTimeFrame_ = 0;

	SDL_Rect dest;
	SDL_Rect clip;
};
