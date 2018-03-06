#pragma once

#include "GameObjectFactory.h"
#include "Player.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "Resources.h"

class PlayerCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity(Game::Instance());
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Player(5));
		e->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
			SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN));
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
		return e;
	}
};
