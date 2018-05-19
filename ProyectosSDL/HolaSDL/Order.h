#pragma once
#include "Interactible.h"
#include "checkML.h"
#include "Inventory.h"

class Order :
	public Interactible
{
public:
	Order();
	~Order();
	virtual void update(Entity* e, Uint32 time);
	bool interact(Entity * e);

	void setPuzzleActive(bool b) { puzzleActive_ = b; };
	bool getPuzzleActive() { return puzzleActive_; };

	void setPuzzleComplete(bool b);
	bool getPuzzleComplete() { return puzzleComplete_; };

private:
	bool puzzleActive_;
	bool puzzleComplete_ = false;
	bool biocida_ = false;
	Inventory* compInvent = nullptr;
};

