#include "CarnePuajAnimationRenderer.h"
#include "Camera.h"
#include "Game.h"




CarnePuajAnimationRenderer::CarnePuajAnimationRenderer(Texture* carnePuaj, Texture* carnePDestroyed, int cooldown, int carneFrames, int destroyedFrames):
	pRenderer_(Game::Instance()->getRenderer()), destroyed_(false), finished_(false), image_(carnePuaj), imageDestroyed_(carnePDestroyed), frames_(carneFrames), destroyedFrames_(destroyedFrames), cont(0), cooldown_(cooldown)
{
}


CarnePuajAnimationRenderer::~CarnePuajAnimationRenderer()
{
}

void CarnePuajAnimationRenderer::render(Entity* o, Uint32 time) {
	dest = RECT(o->getPosition().getX() - Camera::Instance()->getPosition().getX(),
		o->getPosition().getY() - Camera::Instance()->getPosition().getY(),
		o->getWidth(), o->getHeight());
	if (!destroyed_) { //Renderiza la animación de la carne puaj
		clip =
			RECT(cont * image_->getWidth() / frames_, 0,
				image_->getWidth() / frames_, image_->getHeight());
		if (time > actualTime_ + cooldown_) {
			if (cont < frames_ - 1)
				cont++;
			else
				cont = 0;
			actualTime_ = time;
		}
		image_->render(pRenderer_, dest, &clip);
	}
	else if (destroyed_ && !finished_) {  //Si la carne puaj se está destruyendo, pero aún no ha terminado la animación
		clip =
			RECT(cont * imageDestroyed_->getWidth() / destroyedFrames_, 0,
				imageDestroyed_->getWidth() / destroyedFrames_, imageDestroyed_->getHeight());
		if (time > actualTime_ + cooldown_) {
			if (cont < destroyedFrames_ - 1)
				cont++;
			else
			{
				finished_ = true;		//Si ha llegado al último frame de la animación de destrucción ya no renderiza más
				PlayState::Instance()->removeEntity(o);
			}
			actualTime_ = time;
		}
		imageDestroyed_->render(pRenderer_, dest, &clip);
	}
}
