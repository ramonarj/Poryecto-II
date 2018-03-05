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
		Entity* player = new Entity(Game::Instance(), 100, 100);
		player->setWidth(200.0);
		player->setHeight(200.0);
		player->setVelocity(Vector2D(1.0, 0.0));
		player->addComponent(new Player(5));
		player->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 12, true));
		return player;
	}
};

