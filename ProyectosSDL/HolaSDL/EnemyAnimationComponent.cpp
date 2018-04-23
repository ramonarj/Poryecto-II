#include "EnemyAnimationComponent.h"
#include "Camera.h"


EnemyAnimationComponent::EnemyAnimationComponent()
{
}

EnemyAnimationComponent::EnemyAnimationComponent(Uint32 enemyType, Texture * moving, Texture * iddle, Texture * attacking, Texture * diying, Texture * resurrecting,
	Uint32 cooldown, Uint32 iddleFrames, Uint32 movementFrames, Uint32 attackingFrames, Uint32 diyingFrames, Uint32 resurrectingFrames) : iddle_(iddle), moving_(moving), attacking_(attacking),
	diying_(diying), cooldown_(cooldown), iddleFrames_(iddleFrames), movementFrames_(movementFrames), attackingFrames_(attackingFrames), diyingFrames_(diyingFrames), resurrecting_(resurrecting), resurrectingFrames_(resurrectingFrames), enemyType_(enemyType)
{
	cooldownIddle_ = 5 * cooldown_;
}


EnemyAnimationComponent::~EnemyAnimationComponent()
{
}

void EnemyAnimationComponent::render(Entity* o, Uint32 time) {
	SDL_Rect dest
		RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
			o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_Rect clip;

	//MOVIENDOSE
	if (o->getVelocity().magnitude() != 0 && o->getComponent<Character>()->isAlive()) {

		if (actualFrameAttacking_!=0)
			actualFrameAttacking_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if(actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameResurrecting_ != 0)
			actualFrameResurrecting_ = 0;

		clip =
			RECT((actualFrameMoving_) * moving_->getWidth() / movementFrames_,
				dir(o) * moving_->getHeight() / directions_,
				moving_->getWidth() / movementFrames_,
				moving_->getHeight() / directions_);

		lastDir = o->getDirection();

		if (time > actualTime_ + cooldown_) {
			if (actualFrameMoving_ < movementFrames_ - 1)
				actualFrameMoving_++;
			else
				actualFrameMoving_ = 0;
			actualTime_ = time;
		}

		moving_->render(Game::Instance()->getRenderer(), dest, &clip);

	}
	//ATACANDO
	else if ((o->getComponent<Character>()->getAttacking()) && o->getComponent<Character>()->isAlive()) {

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameResurrecting_ != 0)
			actualFrameResurrecting_ = 0;

		clip =
			RECT(actualFrameAttacking_*attacking_->getWidth() / attackingFrames_,
				dirIddle(o) * attacking_->getHeight() / directions_,
				attacking_->getWidth() / attackingFrames_,
				attacking_->getHeight() / directions_);


		if (time > actualTime_ + cooldown_/2) {
			if (actualFrameAttacking_ < attackingFrames_-1) {
				actualFrameAttacking_++;
				if (enemyType_==1 && actualFrameAttacking_==4) {
					o->getComponent<Enemy>()->punch(o);
				}
				else if (enemyType_ == 2 && actualFrameAttacking_ == 9999) {		//DATO A CAMBIAR SEGUN LA ANIMACION DEL ENEMIGO
					o->getComponent<Enemy>()->punch(o);
				}
				else if (enemyType_ == 3 && actualFrameAttacking_ == 9999) {		//DATO A CAMBIAR SEGUN LA ANIMACION DEL ENEMIGO
					o->getComponent<Enemy>()->punch(o);
				}
			}
			else {
				actualFrameAttacking_ = 0;
				(o->getComponent<Character>()->setAttacking(false));
			}
			actualTime_ = time;
		}

		attacking_->render(Game::Instance()->getRenderer(), dest, &clip);

	}
	//MURIENDO
	else if ((!o->getComponent<Character>()->isAlive()) && !o->getComponent<Enemy>()->getResurrecting()) {		//Si ha muerto

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameResurrecting_ != 0)
			actualFrameResurrecting_ = 0;

		clip =
			RECT(actualFrameDiying_*diying_->getWidth() / diyingFrames_,
				dirIddle(o) * diying_->getHeight() / directions_,
				diying_->getWidth() / diyingFrames_,
				diying_->getHeight() / directions_);


		if (time > actualTime_ + cooldown_) {
			if (actualFrameDiying_ < diyingFrames_ - 1)
				actualFrameDiying_++;
			actualTime_ = time;
		}

		diying_->render(Game::Instance()->getRenderer(), dest, &clip);

	}
	else if ((!o->getComponent<Character>()->isAlive()) && o->getComponent<Enemy>()->getResurrecting()) {

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (enemyType_ == 2)
			actualFrameDiying_ = 0;

		if (enemyType_ == 1 || enemyType_ == 3) {
			clip =
				RECT(actualFrameDiying_*diying_->getWidth() / diyingFrames_,
					dirIddle(o) * diying_->getHeight() / directions_,
					diying_->getWidth() / diyingFrames_,
					diying_->getHeight() / directions_);


			if (time > actualTime_ + cooldown_) {
				if (actualFrameDiying_ > 0)
					actualFrameDiying_--;
				else {
					o->getComponent<Enemy>()->revive();
				}
				actualTime_ = time;
			}

			diying_->render(Game::Instance()->getRenderer(), dest, &clip);
		}
		else if (enemyType_ == 2) {
			clip =
				RECT(actualFrameResurrecting_*diying_->getWidth() / diyingFrames_,
					dirIddle(o) * diying_->getHeight() / directions_,
					diying_->getWidth() / diyingFrames_,
					diying_->getHeight() / directions_);


			if (time > actualTime_ + cooldown_) {
				if (actualFrameResurrecting_ < resurrectingFrames_-1)
					actualFrameResurrecting_++;
				else {
					o->getComponent<Enemy>()->revive();
					actualFrameResurrecting_ = 0;
				}
				actualTime_ = time;
			}

			resurrecting_->render(Game::Instance()->getRenderer(), dest, &clip);
		}

	}
	//IDDLE
	else {

		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameResurrecting_ != 0)
			actualFrameResurrecting_ = 0;

		clip =
			RECT(actualFrameIddle_* iddle_->getWidth() / iddleFrames_,
				dirIddle(o) * iddle_->getHeight() / directions_,
				iddle_->getWidth() / (iddleFrames_),
				iddle_->getHeight() / directions_);

		if (time > actualTime_ + cooldownIddle_) {
			if (actualFrameIddle_ < iddleFrames_ -1)
				actualFrameIddle_++;
			else
				actualFrameIddle_ = 0;
			actualTime_ = time;
		}

		iddle_->render(Game::Instance()->getRenderer(), dest, &clip);
	}
}


int EnemyAnimationComponent::dir(Entity* o) {

	Vector2D dir = o->getDirection();
	int direccion = 0;
	if (dir.getX() != 0)
	{
		if (dir.getX() < 0)
			direccion = 2;
		else
			direccion = 3;
	}
	else {
		if (dir.getY() > 0)
			direccion = 0;
		else
			direccion = 1;
	}
	if (dir.getX() != 0 && dir.getY() != 0)
	{
		if (dir.getY() > 0) { direccion = 0; }
		else direccion = 1;
	} 	return direccion;

}

int EnemyAnimationComponent::dirIddle(Entity* o) {
	int x = lastDir.getX();
	int y = lastDir.getY();
	if (x != 0) {
		if (x < 0)
			return 2;
		else
			return 3;
	}
	else {
		if (y > 0)
			return 0;
		else
			return 1;
	}
}