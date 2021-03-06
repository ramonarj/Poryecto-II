#include "NumberKey.h"
#include"Game.h"


NumberKey::NumberKey(SDL_Renderer * pRenderer, int value, int fil, int col, float h, float w) :value_(value), pRenderer_(pRenderer)
{
	
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();
	clicked_ = false;

	key_ = resource->getTexture("Keys");
	pressedKey_ = resource->getTexture("Keys_");

	src = {col * key_->getWidth()/3, fil * key_->getHeight() / 4, key_->getWidth() / 3, key_->getHeight() / 4 }; //Tecla que se coge

	//D�nde va a pintarse
	dest_.h = (key_->getHeight() / 4) * h;
	dest_.w = (key_->getWidth() / 3)* w;
	dest_.x = 417 + 20 * col + dest_.w * col;
	dest_.y = 290 + 20 * fil + dest_.h * fil;
}
bool NumberKey::clicked(int x, int y, Uint32 time) { //Comprueba si se ha pulsado
	if ((x >= dest_.x && x <= (dest_.x + dest_.w)) && (y >= dest_.y && y <= (dest_.y + dest_.h))) {
		timeStarted = time;
		return true;
	}
	else
		return false;
}

void NumberKey::update(Uint32 time) {
	clicked_ = (timeStarted + timeOn >= time) ? true : false;
}

void NumberKey::render(Uint32 time){
	if (!clicked_)
		key_->render(pRenderer_, dest_, &src);
	else
		pressedKey_->render(pRenderer_, dest_, &src);
}


NumberKey::~NumberKey()
{
}
