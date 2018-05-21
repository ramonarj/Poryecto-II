#pragma once
#include "Interactible.h"
#include "PlayState.h"
#include "MessageTrigger.h"
#include "checkML.h"


class SRMap : public Interactible
{
public:
	SRMap();
	~SRMap();

	virtual bool interact(Entity* e);

	void load(Entity* e, int numMap, std::string ori, int calendar);

	virtual void render(Entity* o, Uint32 time);

private:
	string ori_;
	bool mapActive_;
	Texture* image_;
	int numMap_;
};

