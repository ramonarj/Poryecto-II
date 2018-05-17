#pragma once
#include "Component.h"

class DoorAnimation :
	public Component
{
public:
	DoorAnimation(Entity* e);
	virtual ~DoorAnimation();
	virtual void render(Entity* o, Uint32 time);
	void load(string orientacion, int ancha);
	void open() { open_ = true; };

private:
	bool open_ = false;
	Texture* image_ = nullptr;
	Entity* this_;
};

