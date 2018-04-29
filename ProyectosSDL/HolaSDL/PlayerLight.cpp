#include "PlayerLight.h"
#include <algorithm>

PlayerLight::PlayerLight(): horizontal_(true), flipped_(false), currentAgl_(0), destAgl_(0), lastDirection("Right"), currentDirection("Right"), sdlShadow(nullptr) {
	sdlShadow = Game::Instance()->getResourceManager()->getTexture("PlayerLight")->getSdlTexture();
	fade_ = Game::Instance()->getResourceManager()->getTexture("Black");
	
	SDL_SetTextureBlendMode(sdlShadow, SDL_BLENDMODE_ADD);

	shadow_ = Game::Instance()->getResourceManager()->getTexture("PlayerLight");

	player_ = PlayState::Instance()->getPlayer();
}

PlayerLight::~PlayerLight() {
}

double lerp(double a, double b, double f) {
	return a + f * (b - a);
}

void PlayerLight::render(Entity* o, Uint32 time) {
	
	if (player_->getDirection().getX() > 0) {
		destAgl_ = 0;
		currentDirection = "Right";
	}
	else if (player_->getDirection().getX() < 0) {
		destAgl_ = 180;
		currentDirection = "Left";
	}
	else if (player_->getDirection().getY() > 0) {
		destAgl_ = 270;
		currentDirection = "Up";
	}
	else if (player_->getDirection().getY() < 0) {
		destAgl_ = 90;
		currentDirection = "Down";
	}

	// Esto arregla el comportamiento raro en este caso extraordinarios
	if (lastDirection == "Right") {
		if (currentDirection == "Up")
			currentAgl_ += 360;
	}else if (lastDirection == "Up") {
		if (currentDirection == "Right")
			currentAgl_ -= 360;
	}

	lastDirection = currentDirection;

	//SDL_Rect destRect RECT(
	//	o->getPosition().getX(),
	//	o->getPosition().getY(),
	//	Game::Instance()->getWindowWidth(),
	//	Game::Instance()->getWindowHeight());

	SDL_Rect destRect RECT(
		o->getPosition().getX(),
		o->getPosition().getY() - ((Game::Instance()->getWindowWidth() - Game::Instance()->getWindowHeight())/2),
		Game::Instance()->getWindowWidth(),
		Game::Instance()->getWindowWidth());

	currentAgl_ = lerp(currentAgl_, destAgl_, 0.3); //transición al nuevo destino de forma suave

	shadow_->render(Game::Instance()->getRenderer(), destRect, currentAgl_);
	
}
