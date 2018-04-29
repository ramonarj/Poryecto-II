#include "FadeManager.h"
#include "Game.h"


FadeManager::FadeManager()
{
	renderer_ = Game::Instance()->getRenderer();
}


FadeManager::~FadeManager()
{
}

void FadeManager::render(Entity * e, Uint32 time) {

	if (player_ == nullptr) {
		player_ = Game::Instance()->getEntityWithComponent<Player>();
	}
	if (fade_==nullptr) {
		fade_ = Game::Instance()->getResourceManager()->getTexture("Black");
	}

	SDL_Rect dest = RECT(
		player_->getPosition().getX() - Camera::Instance()->getPosition().getX() - Game::Instance()->getWindowWidth() / 2,
		player_->getPosition().getY() - Camera::Instance()->getPosition().getY() - Game::Instance()->getWindowHeight() / 2,
		fade_->getWidth(),
		fade_->getHeight()
	);

	fade_->ChangeAlphaValue(0);

	fade_->render(renderer_, dest);

}

void FadeManager::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	if (event.type == SDL_KEYDOWN) {
		
	}
}