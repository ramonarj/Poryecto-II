#pragma once
#include "Interactible.h"
#include "checkML.h"


class Order :
	public Interactible
{
public:
	Order();
	~Order();
	bool interact(Entity * e);

	void setPuzzleActive(bool b) { puzzleActive_ = b; };
	bool getPuzzleActive() { return puzzleActive_; };

	void setPuzzleComplete(bool b) { puzzleComplete_ = b; };
	bool getPuzzleComplete() { return puzzleComplete_; };

private:
	bool puzzleActive_;
	bool puzzleComplete_ = false;
};

