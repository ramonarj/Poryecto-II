#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image) : image_(image) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(Entity* o, Uint32 time) {
	SDL_Rect rect RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(), 
		o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
		o->getWidth(), o->getHeight());

	image_->render(Game::Instance()->getRenderer(), rect);
}
