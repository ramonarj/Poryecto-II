#include "Register.h"

Register::Register() : registerFile_(0), registerActive_(false), textNote(nullptr)
{
}


Register::~Register()
{
	delete textNote;
}

void Register::interact(Entity * e)
{
	if (!registerActive_) {
		e->addComponent(textNote);
		PlayState::Instance()->getPlayer()->setIsReading(true);
		registerActive_ = true;
	}
	else {
		e->delComponent(textNote);
		PlayState::Instance()->getPlayer()->setIsReading(false);
		registerActive_ = false;
	}
}

void Register::load(int registerFile)
{
	registerFile_ = registerFile;
	textNote = new TextNote(Game::Instance(), "textNotes/Archivo" + to_string(registerFile_) + ".txt", 410, 110, Game::Instance()->getResourceManager()->getTexture("BgRegistro"));
}
