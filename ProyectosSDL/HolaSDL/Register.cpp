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
	loadText(to_string(registerFile_));
	textNote = new TextNote(Game::Instance(), text_, 410, 110, Game::Instance()->getResourceManager()->getTexture("BgRegistro"));
}

bool Register::loadText(const string& filename) {
	ifstream archivo;
	stringstream ss, file;
	string line;

	file << "textNotes/Archivo" << to_string(registerFile_) << ".txt";
	archivo.open(file.str());

	while (getline(archivo, line))
	{
		ss << line << "\n";
	}
	text_ = ss.str();
	archivo.close();
	return true;
}