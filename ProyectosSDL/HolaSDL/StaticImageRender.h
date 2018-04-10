#pragma once
#include "Component.h"
#include "Entity.h"
#include "Game.h"

class StaticImageRender : public Component {
public:
	StaticImageRender(Texture* image);
	virtual ~StaticImageRender();
	virtual void render(Entity* o, Uint32 time);
private:
	Texture* image_;
};

