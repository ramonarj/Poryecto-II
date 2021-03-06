#pragma once
#include "Interactible.h"
#include "TextNote.h"
#include "PlayState.h"
#include "checkML.h"


class Register : public Interactible
{
public:
	Register();
	~Register();

	virtual bool interact(Entity* e);

	void load(int registerFile, std::string dir);
private:
	int registerFile_;
	bool registerActive_;
	TextNote* textNote;
	string text_;
	string ori_;

	bool loadText(const string& filename);
	bool canRead();
};

