#pragma once
#include "Interactible.h"
class Order :
	public Interactible
{
public:
	Order();
	~Order();
	bool interact(Entity * e);

	void setPuzzleActive(bool b) { puzzleActive_ = b; };
	bool getPuzzleActive() { return puzzleActive_; };

private:
	bool puzzleActive_;
};

