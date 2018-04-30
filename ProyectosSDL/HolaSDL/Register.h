#pragma once
#include "Interactible.h"
#include "TextNote.h"
#include "PlayState.h"

class Register : public Interactible
{
public:
	Register();
	~Register();

	virtual void interact(Entity* e);

	void load(int registerFile);
private:
	int registerFile_;
	bool registerActive_;
	TextNote* textNote;
	string text_;

	bool loadText(const string& filename);
};

