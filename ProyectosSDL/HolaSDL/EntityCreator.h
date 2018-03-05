#pragma once

#include "GameObjectFactory.h"
#include "Player.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "Resources.h"
#include "Camera.h"

class PlayerCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity(Game::Instance());
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Player(5));
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
		return e;
	}
};
