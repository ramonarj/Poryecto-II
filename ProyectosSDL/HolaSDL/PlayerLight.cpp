#include "PlayerLight.h"
#include <algorithm>

PlayerLight::PlayerLight(): horizontal_(true), flipped_(false), lightsOn_(false), currentAgl_(0), destAgl_(0) {
	SDL_SetTextureBlendMode(Game::Instance()->getResourceManager()->getTexture("ShadowHorizontal")->getSdlTexture(), SDL_BLENDMODE_MOD);
	SDL_SetTextureBlendMode(Game::Instance()->getResourceManager()->getTexture("ShadowVertical")->getSdlTexture(), SDL_BLENDMODE_MOD);
	SDL_SetTextureBlendMode(Game::Instance()->getResourceManager()->getTexture("Shadow")->getSdlTexture(), SDL_BLENDMODE_MOD);

	shadowH_ = Game::Instance()->getResourceManager()->getTexture("ShadowHorizontal");
	shadowV_ = Game::Instance()->getResourceManager()->getTexture("ShadowVertical");
	shadow_ = Game::Instance()->getResourceManager()->getTexture("Shadow");

	player_ = PlayState::Instance()->getPlayer();
}

PlayerLight::~PlayerLight() {
}

double lerp(double a, double b, double f)
{
	return a + f * (b - a);
}

void PlayerLight::render(Entity* o, Uint32 time) {
	
	if (player_->getDirection().getX() > 0) {
		//cout << "Derecha" << endl;

		horizontal_ = true;
		flipped_ = false;
		destAgl_ = 0;
	}
	else if (player_->getDirection().getX() < 0) {
		//cout << "Izquierda" << endl;

		horizontal_ = true;
		flipped_ = true;
		destAgl_ = 180;
	}
	else if (player_->getDirection().getY() > 0) {
		//cout << "Arriba" << endl;

		horizontal_ = false;
		flipped_ = false;
		destAgl_ = 270;
	}
	else if (player_->getDirection().getY() < 0) {
		//cout << "Abajo" << endl;

		horizontal_ = false;
		flipped_ = true;
		destAgl_ = 90;
	}

	SDL_Rect destRect RECT(
		o->getPosition().getX(),
		o->getPosition().getY(),
		Game::Instance()->getWindowWidth(),
		Game::Instance()->getWindowHeight());

	if ((currentAgl_ - destAgl_) > 180)
		destAgl_ = 360;
	if (destAgl_ == 360)
		destAgl_ = 0;

	currentAgl_ = lerp(currentAgl_, destAgl_, 0.2);
	//cout << currentAgl_ << endl;

	if (lightsOn_)
		(horizontal_? shadowH_ : shadowV_)->render(Game::Instance()->getRenderer(), destRect, 360 / (flipped_ ? 2 : 1));
		//shadow_->render(Game::Instance()->getRenderer(), destRect, currentAgl_);
}

void PlayerLight::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_l)
			lightsOn_ = !lightsOn_;
	}
}

