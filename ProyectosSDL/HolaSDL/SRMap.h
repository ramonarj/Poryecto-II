#pragma once
#include "Interactible.h"
#include "PlayState.h"

class SRMap : public Interactible
{
public:
	SRMap();
	~SRMap();

	virtual void interact(Entity* e);

	void load(int numMap, string ori);

	virtual void render(Entity* o, Uint32 time);

private:
	string ori_;
	bool mapActive_;
	Texture* image_;
};

