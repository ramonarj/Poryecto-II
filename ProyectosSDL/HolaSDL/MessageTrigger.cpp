#include "MessageTrigger.h"
#include "Collisions.h"
#include "PlayState.h"

MessageTrigger::MessageTrigger(std::string message) : message_(message), last(false), messageRenderer(nullptr), player(nullptr) {
}

MessageTrigger::~MessageTrigger() {
}

void MessageTrigger::update(Entity * e, Uint32 time) {
	if (messageRenderer == nullptr)
		messageRenderer = PlayState::Instance()->getMessageRenderer()->getComponent<MessageRenderer>();
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();

	SDL_Rect playerRect = { int(player->getPosition().getX()), int(player->getPosition().getY()), int(player->getWidth()), int(player->getHeight()) };
	SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

	if (Collisions::RectRect(&playerRect, &thisRect)) {
		if (!last) {
			messageRenderer->display(message_/*, player->getPosition().getX() - Camera::Instance()->getPosition().getX(),
				player->getPosition().getY() - (player->getHeight() + 20) - Camera::Instance()->getPosition().getY()*/);
			last = true;
		}
	}
	else if (last) {
		messageRenderer->setDisplaying(false);
		last = false;
	}
}