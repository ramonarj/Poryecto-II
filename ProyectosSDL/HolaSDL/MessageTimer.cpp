#include "MessageTimer.h"
#include "Game.h"
#include "PlayState.h"

MessageTimer::MessageTimer() : messageRenderer(PlayState::Instance()->getMessageRenderer()->getComponent<MessageRenderer>()){
}

void MessageTimer::update(Entity* e, Uint32 time){
	if (on_ && timeInterval_ + timeOn_ < time) {
		messageRenderer->setDisplaying(false);
		on_ = false;
	}
}

void MessageTimer::start(Uint32 timeInterval){
	on_ = true;
	timeOn_ = SDL_GetTicks();
	timeInterval_ = timeInterval * 1000;
}
