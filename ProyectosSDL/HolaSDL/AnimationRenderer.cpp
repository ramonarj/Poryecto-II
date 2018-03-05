#include "AnimationRenderer.h"

AnimationRenderer::AnimationRenderer(Texture* image, Uint32 movementFrames, bool character) : image_(image), movementFrames(movementFrames), character(character)
{
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::render(Entity* o, Uint32 time) {

	SDL_Rect dest
		RECT(o->getPosition().getX(), o->getPosition().getY(), o->getWidth(), o->getHeight());

	SDL_Rect clip;
	if (character){
		if (o->getVelocity().magnitude() != 0){
			clip =
				RECT((frame + 2) * image_->getWidth() / movementFrames,
				dir(o) * image_->getHeight() / movements,
				image_->getWidth() / movementFrames,
				image_->getHeight() / movements);

			lastDir = o->getDirection();

			if (time > actualTime + cooldown){
				if (frame + 2 < movementFrames - 1)
					frame++;
				else
					frame = 0;
				actualTime = time;
			}

		}
		else{
			clip =
				RECT(idleFrame* image_->getWidth() / movementFrames,
				dir(o) * image_->getHeight() / movements,
				image_->getWidth() / movementFrames,
				image_->getHeight() / movements);
			if (time > actualTime + cooldown){
				if (idleFrame < 1)
					idleFrame++;
				else
					idleFrame = 0;
				actualTime = time;
			}
			frame = 0;
		}
	}
	else{
		clip =
			RECT(((time / cooldown) % movementFrames)* image_->getWidth() / movementFrames,
			0,
			image_->getWidth() / movementFrames,
			image_->getHeight() / movements);
	}
	image_->render(o->getGame()->getRenderer(), dest, &clip);
}


int AnimationRenderer::dir(Entity* o){
	int x = lastDir.getX();
	int y = lastDir.getY();
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