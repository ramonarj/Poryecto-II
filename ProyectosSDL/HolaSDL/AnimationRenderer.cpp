#include "AnimationRenderer.h"


AnimationRenderer::AnimationRenderer(Texture* image, Uint32 movementFrames) : image_(image), movementFrames(movementFrames)
{
}


AnimationRenderer::~AnimationRenderer()
{
}
void AnimationRenderer::render(Entity* o, Uint32 time) {

	SDL_Rect rect
		RECT(o->getPosition().getX(), o->getPosition().getY(), o->getWidth(), o->getHeight());
	SDL_Rect clip;
	if (o->getVelocity().magnitude() != 0)
		clip =
		RECT(((time / 100) % movementFrames)* image_->getWidth() / movementFrames, dir(o) * image_->getHeight() / movements, image_->getWidth() / movementFrames, image_->getHeight() / movements);
	else
		clip =
		RECT(0, dir(o) * image_->getHeight() / movements, image_->getWidth() / movementFrames, image_->getHeight() / movements);
	image_->render(o->getGame()->getRenderer(), rect, &clip);

}


int AnimationRenderer::dir(Entity* o){
	int x = o->getDirection().getX();
	int y = o->getDirection().getY();
	if (x != 0){
		if (x < 0)
			return 2;
		else
			return 3;
	}
	else{
		if (y > 0)
			return 0;
		else
			return 1;
	}

}