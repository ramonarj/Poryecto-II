#include "AnimationRenderer.h"
#include "Camera.h"

AnimationRenderer::AnimationRenderer(Texture* image, Uint32 movementFrames, Uint32 attackMovementFrames, Uint32 cooldown, bool character, bool direccionable) : image_(image), movementFrames_(movementFrames), attackMovementFrames_(attackMovementFrames), cooldown_(cooldown), character(character), direccionable(direccionable)
{
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::render(Entity* o, Uint32 time) {

	SDL_Rect dest
		RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
			o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_Rect clip;
	if (character){
		if (o->getVelocity().magnitude() != 0){
			clip =
				RECT((frame_ + 2) * image_->getWidth() / (movementFrames_ + attackMovementFrames_),
				dir(o) * image_->getHeight() / movements_,
				image_->getWidth() / (movementFrames_ + attackMovementFrames_),
				image_->getHeight() / movements_);

			lastDir = o->getDirection();

			if (time > actualTime_ + cooldown_){
				if (frame_ + 2 < movementFrames_ - 1)
					frame_++;
				else
					frame_ = 0;
				actualTime_ = time;
			}

		}
		else if ((o->getComponent<Character>()->getAttacking())){
			
			clip =
				RECT((attackFrames_)* image_->getWidth() / (movementFrames_ + attackMovementFrames_),
				dirIddle(o) * image_->getHeight() / movements_,
				image_->getWidth() / (movementFrames_ + attackMovementFrames_),
				image_->getHeight() / movements_);


			if (time > actualTime_ + cooldown_) {
				if (attackFrames_ < (movementFrames_ + attackMovementFrames_) - 1)
					attackFrames_++;
				else {
					attackFrames_ = 14;
					frame_ = 0;
					(o->getComponent<Character>()->setAttacking(false));
				}

				actualTime_ = time;
			}

		}
		else {
			clip =
				RECT(idleFrame_* image_->getWidth() / (movementFrames_ + attackMovementFrames_),
					dirIddle(o) * image_->getHeight() / movements_,
					image_->getWidth() / (movementFrames_ + attackMovementFrames_),
					image_->getHeight() / movements_);

			if (time > actualTime_ + cooldownIddle_) {
				if (idleFrame_ < 1)
					idleFrame_++;
				else
					idleFrame_ = 0;
				actualTime_ = time;
			}
			frame_ = 0;
		}
	}
	else if(direccionable){
		clip =
			RECT(((time / cooldown_) % movementFrames_)* image_->getWidth() / movementFrames_,
			dir(o) * image_->getHeight()/movements_,
			image_->getWidth() / movementFrames_,
			image_->getHeight() / movements_);

		if (time > actualTime_ + cooldown_){
			if (frame_< movementFrames_ - 1)
				frame_++;
			else
				frame_ = 0;
			actualTime_ = time;
		}
	}
	else{
		clip =
			RECT(((time / cooldown_) % movementFrames_)* image_->getWidth() / movementFrames_,
			0,
			image_->getWidth() / movementFrames_,
			image_->getHeight());

		if (time > actualTime_ + cooldown_){
			if (frame_  < movementFrames_ - 1)
				frame_++;
			else
				frame_ = 0;
			actualTime_ = time;
		}
	}

	image_->render(Game::Instance()->getRenderer(), dest, &clip);
}

int AnimationRenderer::dir(Entity* o) {

	Vector2D dir = o->getDirection();
	int direccion = 0;
	if (dir.getX() != 0) 
	{ if (dir.getX() < 0) 
		direccion = 2;
	else 			
		direccion = 3; }
	else { if (dir.getY() > 0)
		direccion = 0; 		
	else 			
		direccion = 1; 
	} 	
	if (dir.getX() != 0 && dir.getY() != 0) 
	{ if (dir.getY() > 0) { direccion = 0; }
	else direccion = 1; } 	return direccion;

}

int AnimationRenderer::dirIddle(Entity* o){
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