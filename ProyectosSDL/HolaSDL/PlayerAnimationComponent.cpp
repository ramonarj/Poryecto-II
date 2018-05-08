#include "PlayerAnimationComponent.h"



PlayerAnimationComponent::PlayerAnimationComponent()
{
}

PlayerAnimationComponent::PlayerAnimationComponent(Texture * iddle, Texture * moving, Texture * attackingCrowbar, Texture * attackingPipe, 
	Texture * attackingCrutch, Texture * attackingAxe, Texture * diying, Texture * awakening,
	Uint32 cooldown, Uint32 iddleFrames, Uint32 movementFrames, Uint32 attackingFrames,
	Uint32 diyingFrames, Uint32 awakeningFrames) : iddle_(iddle), moving_(moving), attackingCrowbar_(attackingCrowbar), attackingPipe_(attackingPipe), attackingCrutch_(attackingCrutch), attackingAxe_(attackingAxe),
	diying_(diying), awakening_(awakening), cooldown_(cooldown), iddleFrames_(iddleFrames), movementFrames_(movementFrames), attackingFrames_(attackingFrames), diyingFrames_(diyingFrames), awakeningFrames_(awakeningFrames),
	alpha_(255)
{

	attackingTextures_.push_back(attackingCrowbar_);		//ORDEN CROWBAR, PIPE, CRUTCH, AXE
	attackingTextures_.push_back(attackingPipe_);
	attackingTextures_.push_back(attackingCrutch_);
	attackingTextures_.push_back(attackingAxe_);
}


PlayerAnimationComponent::~PlayerAnimationComponent()
{
}


void PlayerAnimationComponent::render(Entity* o, Uint32 time) {
	SDL_Rect dest
		RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
			o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_Rect clip;

	//MOVIENDOSE
	if ((o->getComponent<Player>()->isAlive()) && o->getVelocity().magnitude() != 0) {

		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameAwakening_ != 0)
			actualFrameAwakening_ = 0;

		clip =
			RECT((actualFrameMoving_)* moving_->getWidth() / movementFrames_,
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
	else if ((o->getComponent<Player>()->isAlive()) && (o->getComponent<Character>()->getAttacking())) {

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameAwakening_ != 0)
			actualFrameAwakening_ = 0;

		if(attacking_!= attackingTextures_[weapon(o)])		//le pongo a la textura attacking la correspondiente al arma equipada
			attacking_ = attackingTextures_[weapon(o)];

		clip =
			RECT(actualFrameAttacking_*attacking_->getWidth() / attackingFrames_,
				dirIddle(o) * attacking_->getHeight() / directions_,
				attacking_->getWidth() / attackingFrames_,
				attacking_->getHeight() / directions_);


		if (time > actualTime_ + 2*cooldown_ / 3) {
			if (actualFrameAttacking_ < attackingFrames_ - 1) {
				actualFrameAttacking_++;
				if (actualFrameAttacking_ == 4) {
					o->getComponent<Player>()->setPunch(true);
				}
			}
			else {
				actualFrameAttacking_ = 0;
				o->getComponent<Character>()->setAttacking(false);
				o->getComponent<Player>()->setPunch(false);
			}
			actualTime_ = time;
		}

		attacking_->render(Game::Instance()->getRenderer(), dest, &clip);

	}
	//MURIENDO
	else if ((!o->getComponent<Character>()->isAlive()) && !o->getComponent<Player>()->getAwakening()) {		//Si ha muerto

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameAwakening_ != 0)
			actualFrameAwakening_ = 0;

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

	//DESPERTANDO
	else if ((o->getComponent<Player>()->isAlive()) && o->getComponent<Player>()->getAwakening()) {

		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameIddle_ != 0)
			actualFrameIddle_ = 0;
		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;

			clip =
				RECT(actualFrameAwakening_*awakening_->getWidth() / awakeningFrames_,
					0,
					awakening_->getWidth() / awakeningFrames_,
					awakening_->getHeight());


			if (time > actualTime_ + cooldown_*5) {
				if (actualFrameAwakening_ < awakeningFrames_-1)
					actualFrameAwakening_++;
				else {
					o->getComponent<Player>()->setAwakening(false);		//Ya no está despertandose
					o->setDirection(Vector2D(0.0, -1.0));
				}
				actualTime_ = time;
			}
		awakening_->render(Game::Instance()->getRenderer(), dest, &clip);
	}
	//IDDLE
	else {

		if (actualFrameAttacking_ != 0)
			actualFrameAttacking_ = 0;
		if (actualFrameMoving_ != 0)
			actualFrameMoving_ = 0;
		if (actualFrameDiying_ != 0)
			actualFrameDiying_ = 0;
		if (actualFrameAwakening_ != 0)
			actualFrameAwakening_ = 0;

		clip =
			RECT(actualFrameIddle_* iddle_->getWidth() / iddleFrames_,
				dirIddle(o) * iddle_->getHeight() / directions_,
				iddle_->getWidth() / (iddleFrames_),
				iddle_->getHeight() / directions_);

		if (time > actualTime_ + cooldownIddle_) {
			if (actualFrameIddle_ < iddleFrames_ - 1)
				actualFrameIddle_++;
			else
				actualFrameIddle_ = 0;
			actualTime_ = time;
		}

		iddle_->render(Game::Instance()->getRenderer(), dest, &clip);
	}
}

void PlayerAnimationComponent::invincible()
{
	if (alpha_ == 255) alpha_ = 100;
	else alpha_ = 255;

	iddle_->ChangeAlphaValue(alpha_);
	moving_->ChangeAlphaValue(alpha_);
	diying_->ChangeAlphaValue(alpha_);
	awakening_->ChangeAlphaValue(alpha_);
	for (Texture* t : attackingTextures_)
		t->ChangeAlphaValue(alpha_);
}

void PlayerAnimationComponent::removeTransparency()
{
	alpha_ = 255;
	iddle_->ChangeAlphaValue(alpha_);
	moving_->ChangeAlphaValue(alpha_);
	diying_->ChangeAlphaValue(alpha_);
	awakening_->ChangeAlphaValue(alpha_);
	for (Texture* t : attackingTextures_)
		t->ChangeAlphaValue(alpha_);
}


int PlayerAnimationComponent::weapon(Entity * o)
{
	weaponId = o->getComponent<Player>()->getWeaponId();
	return weaponId;
}

int PlayerAnimationComponent::dir(Entity* o) {

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
	} 	
	return direccion;

}

int PlayerAnimationComponent::dirIddle(Entity* o) {
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