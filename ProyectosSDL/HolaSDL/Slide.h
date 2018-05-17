#pragma once
#include "Interactible.h"
#include "SlidingPuzzle.h"
#include "checkML.h"


class Slide : public Interactible
{
public:
	Slide();
	~Slide();

	virtual bool interact(Entity* e);

	void setPuzzleComplete(bool b) { puzzleComplete_ = b; };
	bool getPuzzleComplete() { return puzzleComplete_; };

private:
	bool puzzleComplete_ = false;
};

