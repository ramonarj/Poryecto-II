#pragma once

#include "GameObjectFactory.h"
#include "Player.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "Resources.h"

class EntityCreator : public BaseCreator
{
protected:
	Entity* e = nullptr;
};

class PlayerCreator : public EntityCreator
{
public:
	Entity* createEntity()
	{
		e = new Entity(Game::Instance(), 100, 100);
		e->setWidth(200.0);
		e->setHeight(200.0);
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addLogicComponent(new Player(5));
		e->addRenderComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 12));
		return e;
	}
};
