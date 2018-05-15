#include "Sign.h"



Sign::Sign() : textNote_(nullptr), messageTrigger_(nullptr), time_(0), sign_(false), signOn_(0), signTime_(2000)
{
}


Sign::~Sign()
{
}

void Sign::load(Entity* e, int numSign, std::string ori)
{
	ifstream archivo;
	stringstream ss, file;
	string line;

	file << "signs/Sign" << numSign << ".txt";

	archivo.open(file.str());

	while (getline(archivo, line))
	{
		ss << line << "\n";
	}

	archivo.close();

	e->addComponent(new TextNote(Game::Instance(), ss.str(), 0, 0, nullptr));
	textNote_ = e->getComponent<TextNote>();
	textNote_->setEnabled(false);
	textNote_->setColor({ 255, 255, 255, 255 });

	messageTrigger_ = e->getComponent<MessageTrigger>();

	KBmessage_ = messageTrigger_->getKBMessage();
	CNTmessage_ = messageTrigger_->getCNTmessage();

	ori_ = ori;
}

bool Sign::interact(Entity * e)
{
	if (!sign_ && canLookSign())
	{
		textNote_->setEnabled(true);
		messageTrigger_->setMessage("", true);
		sign_ = true;
		signOn_ = SDL_GetTicks();
		return true;
	}
	return false;
}

bool Sign::canLookSign()
{
	PlayerAnimationComponent* animPlayer = PlayState::Instance()->getPlayer()->getComponent<PlayerAnimationComponent>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}

void Sign::update(Entity * e, Uint32 time)
{
	if (sign_ && (signOn_ + signTime_ < time))
	{
		textNote_->setEnabled(false);
		messageTrigger_->setMessage(KBmessage_, CNTmessage_, true);
		sign_ = false;
	}
}

