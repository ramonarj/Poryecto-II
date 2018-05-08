#pragma once
#include "Component.h"
#include "Collisions.h"
#include "CountdownManager.h"

class Countdown : public Component
{
public:
	Countdown();
	~Countdown();

	virtual void update(Entity* e, Uint32 time);
	void load(int active);

	CountdownManager* countdownManager_;

private:
	bool activeCountdown_;
};
