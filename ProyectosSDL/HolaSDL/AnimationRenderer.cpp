#include "AnimationRenderer.h"

AnimationRenderer::AnimationRenderer(Texture* image, Texture* imageAttack, Uint32 movementFrames, Uint32 attackMovementFrames, bool character) : image_(image), imageAttack_(imageAttack), movementFrames_(movementFrames), attackMovementFrames_(attackMovementFrames), character(character)
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
				RECT((frame_ + 2) * image_->getWidth() / movementFrames_,
				dir(o) * image_->getHeight() / movements_,
				image_->getWidth() / movementFrames_,
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
				RECT((attackFrames_) * imageAttack_->getWidth() / attackMovementFrames_,
					dir(o) * imageAttack_->getHeight() / movements_,
					imageAttack_->getWidth() / attackMovementFrames_,
					imageAttack_->getHeight() / movements_);

			lastDir = o->getDirection();

			if (time > actualTime_ + cooldown_) {
				if (attackFrames_ < attackMovementFrames_ - 1)
					attackFrames_++;
				else {
					attackFrames_ = 0;
					frame_ = 0;
					(o->getComponent<Character>()->setAttacking(false));
				}

				actualTime_ = time;
			}

		}
		else {
			clip =
				RECT(idleFrame_* image_->getWidth() / movementFrames_,
					dirIddle(o) * image_->getHeight() / movements_,
					image_->getWidth() / movementFrames_,
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
	else{
		clip =
			RECT(((time / cooldown_) % movementFrames_)* image_->getWidth() / movementFrames_,
			0,
			image_->getWidth() / movementFrames_,
			image_->getHeight() / movements_);
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