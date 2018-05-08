#include "CountdownManager.h"
#include "Game.h"


CountdownManager::CountdownManager() : Component(), countdown_(false), countdownOn_(0), countdownTime_(0), 
										messageRenderer(nullptr), transparentCont_(false), timeToRed_(5000)
{
}


CountdownManager::~CountdownManager()
{

}

void CountdownManager::update(Entity * e, Uint32 time)
{
	if (messageRenderer == nullptr)
	{
		messageRenderer = new Entity();
		messageRenderer->addComponent(new MessageRenderer());
		messageRenderer->addComponent(new MessageTimer());
		messageRenderer->getComponent<MessageRenderer>()->setFont(Game::Instance()->getResourceManager()->getFont("VCR_OSD_MONO_32"));
		Game::Instance()->getStateMachine()->currentState()->getStage()->push_back(messageRenderer);
	}

	if (countdown_)
	{
		int min = 0, seg = ((countdownOn_ + countdownTime_) - time) / 1000 + 1;
		string m, s;
		if (seg >= 60)
		{
			min = int(seg / 60);
			seg = seg % 60;
		}
		if (min < 10)  m = "0" + to_string(min);
		else m = to_string(min);
		if (seg < 10) s = "0" + to_string(seg);
		else s = to_string(seg);


		messageRenderer->getComponent<MessageRenderer>()->display(m + ":" + s,
			Game::Instance()->getWindowWidth() / 1.1, Game::Instance()->getWindowHeight() / 20);
	}
	else
		messageRenderer->getComponent<MessageRenderer>()->setMessage("");

	if (countdown_)
	{
		if (countdownOn_ + countdownTime_ < time)
		{
			messageRenderer->getComponent<MessageRenderer>()->setMessage("00:00");
			messageRenderer->getComponent<MessageTimer>()->start(0.5);
			Game::Instance()->getEntityWithComponent<Player>()->getComponent<Character>()->setDie();
			countdown_ = false;
		}
		else if (countdownOnOff_ + 500 < time)
		{
			transparentCont_ = !transparentCont_;
			messageRenderer->getComponent<MessageRenderer>()->setEnabled(transparentCont_);
			countdownOnOff_ = SDL_GetTicks();
		}

		if ((countdownOn_ + countdownTime_) - time <= timeToRed_)
			messageRenderer->getComponent<MessageRenderer>()->setColor({ 255, 0, 0, 255 });
	}
}

void CountdownManager::render(Entity * e, Uint32 time)
{
}

void CountdownManager::startCountdown(int count)
{
	countdown_ = true;
	transparentCont_ = true;
	countdownTime_ = count;
	countdownOnOff_ = SDL_GetTicks();
	countdownOn_ = SDL_GetTicks();
	messageRenderer->getComponent<MessageRenderer>()->setColor({ 255, 255, 255, 255 });
}
