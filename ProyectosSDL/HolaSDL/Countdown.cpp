#include "Countdown.h"
#include "Game.h"


Countdown::Countdown(): Component(), activeCountdown_(false), countdownManager_(nullptr)
{
}


Countdown::~Countdown()
{
}

void Countdown::update(Entity * e, Uint32 time)
{
	if (countdownManager_ == nullptr)
		countdownManager_ = Game::Instance()->getEntityWithComponent<CountdownManager>()->getComponent<CountdownManager>();

	if (Collisions::RectRect(&Game::Instance()->getEntityWithComponent<Player>()->getRect(), &e->getRect()))
	{
		if (!countdownManager_->getCountdown() && activeCountdown_ && Game::Instance()->getEntityWithComponent<Player>()->getComponent<Character>()->isAlive())
			countdownManager_->startCountdown();
		else if (countdownManager_->getCountdown() && !activeCountdown_  && Game::Instance()->getEntityWithComponent<Player>()->getComponent<Character>()->isAlive())
			countdownManager_->setCountdown(false);
	}
}

void Countdown::load(int active)
{
	activeCountdown_ = active;
}
