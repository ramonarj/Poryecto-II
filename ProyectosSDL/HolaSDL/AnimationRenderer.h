#pragma once
#include "RenderComponent.h"
class AnimationRenderer :
	public RenderComponent
{
public:
	AnimationRenderer(Texture* image, Uint32 movementFrames);
	virtual ~AnimationRenderer();
	virtual void render(GameObject* o, Uint32 time);
	virtual int dir(GameObject* o);
private:
	Texture* image_;
	Uint32 movementFrames, movements = 4;
};

