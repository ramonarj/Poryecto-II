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
		e->addComponent(new Player());
		e->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
			SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN));
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
		return e;
	}
};

class EnemyCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity(Game::Instance());
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Enemy());
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
		return e;
	}
};

class ItemCreator : public BaseCreator
{
public:
	ItemCreator(ItemType type) : type_(type) {};
	Entity* createEntity() const
	{
		Entity* e = new Entity(Game::Instance());
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Item(type_));
		e->addComponent(new ImageRenderer(Game::Instance()->getResources()->getImageTexture(Resources::Crowbar)));
		//falta que se cambie el resource por el resourceManager
		return e;
	}
private:
	ItemType type_;
};