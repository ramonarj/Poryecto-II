#include "Register.h"

Register::Register() : registerFile_(0), registerActive_(false), textNote(nullptr)
{
}


Register::~Register()
{
	delete textNote;
}

bool Register::interact(Entity * e)
{
	if ((ori_ != "" && canRead()) || ori_ == "")
	{
		if (!registerActive_) {
			e->addComponent(textNote);
			PlayState::Instance()->getPlayer()->setIsReading(true);
			registerActive_ = true;
			int random = rand() % 100;
			if(random > 69) Game::Instance()->getResourceManager()->getSound("EliseThemeSound")->play();
		}
		else {
			e->removeComponent(textNote);
			PlayState::Instance()->getPlayer()->setIsReading(false);
			registerActive_ = false;
		}
		return true;
	}
	return false;
}

void Register::load(int registerFile, std::string dir)
{
	registerFile_ = registerFile;
	ori_ = dir;
	loadText(to_string(registerFile_));
	if (registerFile == 1) {	//Como es unico se podria hacer entero en photoshop
		textNote = new TextNote(Game::Instance(), "", 410, 110, Game::Instance()->getResourceManager()->getTexture("BgBook"));
	}
	else if (registerFile == 2)	//Variacion del registro normal pero con la foto de Elise
		textNote = new TextNote(Game::Instance(), text_, 410, 130, Game::Instance()->getResourceManager()->getTexture("BgRegistroWithPic"));	//Cambiar esto TEMPORAL
	else
		textNote = new TextNote(Game::Instance(), text_, 410, 130, Game::Instance()->getResourceManager()->getTexture("BgRegistro"));
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

bool Register::canRead()
{
	PlayerAnimationComponent* animPlayer = PlayState::Instance()->getPlayer()->getComponent<PlayerAnimationComponent>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}