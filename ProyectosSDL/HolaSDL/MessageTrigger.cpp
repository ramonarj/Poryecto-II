#include "MessageTrigger.h"
#include "Collisions.h"
#include "PlayState.h"

MessageTrigger::MessageTrigger(std::string message) : KBmessage_(message), CNTmessage_(message), last(false), messageRenderer(nullptr),
player(nullptr), CNTcomp(nullptr) {
}

MessageTrigger::MessageTrigger(std::string KBmessage, std::string CNTmessage) : KBmessage_(KBmessage), CNTmessage_(CNTmessage),
last(false), messageRenderer(nullptr), player(nullptr), CNTcomp(nullptr) {
}

MessageTrigger::~MessageTrigger() {
}

void MessageTrigger::update(Entity * e, Uint32 time) {
	if (messageRenderer == nullptr)
		messageRenderer = PlayState::Instance()->getMessageRenderer()->getComponent<MessageRenderer>();
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();
	if (CNTcomp == nullptr)
		CNTcomp = player->getComponent<ControllerInputComponent>();

	SDL_Rect playerRect = { int(player->getPosition().getX()), int(player->getPosition().getY()), int(player->getWidth()), int(player->getHeight()) };
	SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

	//cout << CNTmessage_ << endl;

	if (Collisions::RectRect(&playerRect, &thisRect)) {
		if (!last) {
			if (!CNTcomp->joysticksInitialised())
				messageRenderer->display(KBmessage_);
			else {
				messageRenderer->display(CNTmessage_);
			}
			last = true;
		}
	}
	else if (last) {
		messageRenderer->setDisplaying(false);
		last = false;
	}
}

void MessageTrigger::setMessage(std::string message) {
	KBmessage_ = message;
	CNTmessage_ = message;
}

void MessageTrigger::setMessage(std::string KBmessage, std::string CNTmessage) {
	KBmessage_ = KBmessage;
	CNTmessage_ = CNTmessage;
}
