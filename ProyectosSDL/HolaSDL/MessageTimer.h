#pragma once
#include "Component.h"
#include "MessageRenderer.h"
#include "checkML.h"


class MessageTimer : public Component { //Para deshabilitar el Badge pasado un X tiempo
public:
	MessageTimer();
	virtual ~MessageTimer() {};
	virtual void update(Entity* e, Uint32 time);
	void start(Uint32 timeInterval); // Tiempo que tarda en desactivarse (en segundos)
	bool isOn() { return on_; };

private:
	bool on_;
	Uint32 timeOn_;
	Uint32 timeInterval_;
	MessageRenderer* messageRenderer;
};

