#pragma once
#include "Component.h"
#include "MessageRenderer.h"

class MessageTrigger : public Component {
public:
	MessageTrigger(std::string message);
	~MessageTrigger();
	virtual void update(Entity* e, Uint32 time);
private:
	std::string message_;
	bool last;

	MessageRenderer* messageRenderer;
	Entity* player;

	SDL_Rect thisRect;
};

