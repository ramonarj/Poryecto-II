#include "PlayerLight.h"

PlayerLight::PlayerLight(): horizontal_(true), flipped_(false), lightsOn_(false) {
	SDL_SetTextureBlendMode(Game::Instance()->getResourceManager()->getTexture("ShadowHorizontal")->getSdlTexture(), SDL_BLENDMODE_MOD);
	SDL_SetTextureBlendMode(Game::Instance()->getResourceManager()->getTexture("ShadowVertical")->getSdlTexture(), SDL_BLENDMODE_MOD);

	shadowH_ = Game::Instance()->getResourceManager()->getTexture("ShadowHorizontal");
	shadowV_ = Game::Instance()->getResourceManager()->getTexture("ShadowVertical");
	player_ = PlayState::Instance()->getPlayer();
}

PlayerLight::~PlayerLight() {
}

void PlayerLight::render(Entity* o, Uint32 time) {
	
	if (player_->getDirection().getX() > 0) {
		cout << "Derecha" << endl;

		horizontal_ = true;
		flipped_ = false;
	}
	else if (player_->getDirection().getX() < 0) {
		cout << "Izquierda" << endl;

		horizontal_ = true;
		flipped_ = true;
	}
	else if (player_->getDirection().getY() > 0) {
		cout << "Arriba" << endl;

		horizontal_ = false;
		flipped_ = false;
	}
	else if (player_->getDirection().getY() < 0) {
		cout << "Abajo" << endl;

		horizontal_ = false;
		flipped_ = true;
	}

	SDL_Rect destRect RECT(
		o->getPosition().getX(),
		o->getPosition().getY(),
		Game::Instance()->getWindowWidth(),
		Game::Instance()->getWindowHeight());
	if (lightsOn_)
		(horizontal_? shadowH_ : shadowV_)->render(Game::Instance()->getRenderer(), destRect, 360 / (flipped_ ? 2 : 1));
}

void PlayerLight::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_l)
			lightsOn_ = !lightsOn_;
	}
}

//double lerp(double a, double b, double f)
//{
//	return a + f * (b - a);
//}