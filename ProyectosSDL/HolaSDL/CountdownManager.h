#pragma once
#include "Component.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"

class CountdownManager : public Component
{
public:
	CountdownManager();
	~CountdownManager();

	virtual void update(Entity* e, Uint32 time);
	virtual void render(Entity* e, Uint32 time);

	void startCountdown();

	bool getCountdown() { return countdown_; };
	void setCountdown(bool b) { countdown_ = b; };

	Entity* messageRenderer;

private:
	bool countdown_;
	Uint32 countdownOn_;
	Uint32 countdownOnOff_;
	Uint32 countdownTime_;
	bool transparentCont_;

};
