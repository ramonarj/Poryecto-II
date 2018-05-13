#include "DoorAnimation.h"
#include "Door.h"
#include "Camera.h"


DoorAnimation::DoorAnimation(Entity* e)
{
	this_ = e;
}


DoorAnimation::~DoorAnimation()
{
}

void DoorAnimation::render(Entity* o, Uint32 time) {
	SDL_Rect dest
		RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
			o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_Rect clip;

	if (open_ == false) {
		open_ = !o->getComponent<Door>()->getNeedKey();
	}

	if (!open_) {
		clip = RECT (0,0,image_->getWidth() / 2, image_->getHeight());
	}
	else {
		clip = RECT(image_->getWidth() / 2, 0, image_->getWidth() / 2, image_->getHeight());
	}

	image_->render(Game::Instance()->getRenderer(), dest, &clip);
}

void DoorAnimation::load(string orientacion, int ancha)
{
	if (this_->getComponent<Door>()->getDoorNum() == 1000) {
		image_ = Game::Instance()->getResourceManager()->getTexture("PuertaEmergencia");
	}
	else if (orientacion == "norte") {
		if (ancha)
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaArriba");
		else
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaArribaEstrecha");
	}
	else if (orientacion == "sur")
	{
		if (ancha)
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaAbajo");
		else
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaAbajoEstrecha");
	}
	else if (orientacion == "este")
	{
		if (ancha)
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaDerecha");
		else
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaDerechaEstrecha");
	}
	else if (orientacion == "oeste")
	{
		if (ancha)
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaIzquierda");
		else
			image_ = Game::Instance()->getResourceManager()->getTexture("PuertaIzquierdaEstrecha");
	}
}
