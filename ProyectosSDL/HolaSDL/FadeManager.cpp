#include "FadeManager.h"
#include "Game.h"


FadeManager::FadeManager() : Component(), fade_(nullptr), alpha_(0), difAlpha_(0)
{
}

FadeManager::FadeManager(Texture * texture) : Component(), fade_(texture), alpha_(MAX_FADE_ALPHA), difAlpha_(15)
{
}


FadeManager::~FadeManager()
{
	delete fade_;
}

void FadeManager::render(Entity * e, Uint32 time) {

	SDL_Rect dest = RECT(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight());

	if (PlayState::Instance()->getPlayer()->getComponent<Player>()->getTeleport())
	{
		if (alpha_ < MAX_FADE_ALPHA)
			alpha_ += difAlpha_;
		if (alpha_ > 255 - difAlpha_)
			alpha_ = MAX_FADE_ALPHA;
	}
	else
	{
		if (alpha_ > 0) 
			alpha_ -= difAlpha_;
		if (alpha_ < difAlpha_)
			alpha_ = 0;
	}
	fade_->ChangeAlphaValue(alpha_);


	fade_->render(Game::Instance()->getRenderer(), dest);
}

void FadeManager::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	/*if (event.type == SDL_KEYDOWN) {
		
	}*/
}