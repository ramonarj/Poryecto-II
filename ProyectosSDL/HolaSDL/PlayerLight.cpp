#include "PlayerLight.h"
#include <algorithm>

PlayerLight::PlayerLight(): horizontal_(true), flipped_(false), currentAgl_(0), destAgl_(0), lastDirection("Right"), currentDirection("Right"), sdlShadow(nullptr) {
	sdlShadow = Game::Instance()->getResourceManager()->getTexture("PlayerLight")->getSdlTexture();
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
	
	if (player_->getDirection().getX() > 0)
		destAgl_ = 0;
	else if (player_->getDirection().getX() < 0)
		destAgl_ = 180;
	else if (player_->getDirection().getY() > 0)
		destAgl_ = -90;
	else if (player_->getDirection().getY() < 0)
		destAgl_ = 90;

	//if (player_->getDirection().getX() > 0)
	//	currentDirection = "Right";
	//else if (player_->getDirection().getX() < 0)
	//	currentDirection = "Left";
	//else if (player_->getDirection().getY() > 0)
	//	currentDirection = "Up";
	//else if (player_->getDirection().getY() < 0)
	//	currentDirection = "Down";

	//if (currentDirection != lastDirection) {
	//	if (lastDirection == "Right") {
	//		if (currentDirection == "Up")
	//			destAgl_ -= 90;
	//		else if (currentDirection == "Down")
	//			destAgl_ += 90;
	//		else if (currentDirection == "Left")
	//			destAgl_ -= 180;
	//	}
	//	else if (lastDirection == "Left") {
	//		if (currentDirection == "Up")
	//			destAgl_ += 90;
	//		else if (currentDirection == "Down")
	//			destAgl_ -= 90;
	//		else if (currentDirection == "Right")
	//			destAgl_ -= 180;
	//	}
	//	else if (lastDirection == "Up") {
	//		if (currentDirection == "Right")
	//			destAgl_ += 90;
	//		else if (currentDirection == "Left")
	//			destAgl_ -= 90;
	//		else if (currentDirection == "Down")
	//			destAgl_ -= 180;
	//	}
	//	else if (lastDirection == "Down") {
	//		if (currentDirection == "Right")
	//			destAgl_ -= 90;
	//		else if (currentDirection == "Left")
	//			destAgl_ += 90;
	//		else if (currentDirection == "Up")
	//			destAgl_ -= 180;
	//	}

	//	lastDirection = currentDirection;
	//}

	//cout << lastDirection << endl;

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

	shadow_->render(Game::Instance()->getRenderer(), destRect, currentAgl_);
}
