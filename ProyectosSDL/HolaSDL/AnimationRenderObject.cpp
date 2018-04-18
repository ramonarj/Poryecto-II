#include "AnimationRenderObject.h"
#include "SecurityCamera.h"


AnimationRenderObject::AnimationRenderObject()
{
}


AnimationRenderObject::AnimationRenderObject(Texture* image, int cooldown=100, bool chest = false, bool camera = false, bool on = true) : chest_(chest), camera_(camera), on_(on), image_(image), cooldown_(cooldown) {



}

AnimationRenderObject::~AnimationRenderObject()
{

}



void AnimationRenderObject::render(Entity * o, Uint32 time){

	if (orientation_ == -1) {
		if(camera_)
			orientation_ = o->getComponent<SecurityCamera>()->getNumCamera();
	}

	dest = RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
		o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
		o->getWidth(), o->getHeight());

	if (on_) {

		if (chest_) {

			//SI ES EL COFRE

		}

		else if (camera_) {

			//SI ES UNA CAMARA

			clip = RECT((frame_)* image_->getWidth() / (7),
				orientation_ * image_->getHeight() / (4),
				image_->getWidth() / (7),
				image_->getHeight() / 4);

			if (time > lastTimeFrame_ + cooldown_) {
				if (way_ == true){
					frame_+=1;
					if (frame_ == 6)
						way_ = false;
				}
				else {
					frame_--;
					if (frame_ == 0)
						way_ = true;
				}
				lastTimeFrame_ = time;
			}
		}

		else {

			//SI ES OTRO OBJETO DEL SUELO (REGISTROS,ARMAS,LLAVES...)
			clip = 
				RECT((frame_)* image_->getWidth() / (2),
				0,
				image_->getWidth() / (2),
				image_->getHeight());

			if (time > lastTimeFrame_ + cooldown_) {
				if (frame_!=1) {
					frame_=1;
				}
				else{
					frame_=0;
				}
				lastTimeFrame_ = time;
			}
		}
	}
	else {

		clip =
			RECT((0)* image_->getWidth() / (2),		//Si está apagado se coge el frame 0
				0,
				image_->getWidth() / (2),
				image_->getHeight());

	}

	image_->render(Game::Instance()->getRenderer(), dest, &clip);
}