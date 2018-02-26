#pragma once

#include "GameObject.h"

class Component {

private:
	bool enabled_;

public:
	void setEnabled(bool enabled) { enabled_ = enabled; };
	bool isEnabled() { return enabled_; };
	Component();
	virtual ~Component();

	virtual void update(GameObject* o, Uint32 time) = 0;
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event) = 0;
	virtual void render(GameObject* o, Uint32 time) = 0;

};

