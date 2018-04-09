#include "StaticImageRender.h"

StaticImageRender::StaticImageRender(Texture* image) : image_(image) {
}

StaticImageRender::~StaticImageRender() {
}

void StaticImageRender::render(Entity* o, Uint32 time) {
	SDL_Rect rect RECT(
		o->getPosition().getX(),
		o->getPosition().getY(),
		o->getWidth(),
		o->getHeight());

	image_->render(Game::Instance()->getRenderer(), rect);
}
