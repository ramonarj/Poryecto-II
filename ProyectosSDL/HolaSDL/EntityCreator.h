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
		
		e->addComponent(chooseItemType(type_));
		e->addComponent(new ImageRenderer(Game::Instance()->getResourceManager()->getTexture(toString(type_))));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	};
	Component* chooseItemType(const ItemType type) const{
		Item* i;
		switch (type)
		{
		case Stick:
			i = new Weapon(type);
			break;
		case Lever:
			i = new Weapon(type);
			break;
		case Pipe:
			i = new Weapon(type);
			break;
		case Ax:
			i = new Weapon(type);
			break;
		case Firstaid:
			i = new FirstAid();
			break;
		case Insulationtape:
			i = new InsulationTape();
			break;
		default:
			i = new Item(type);
			break;
		}
		
		return i;
	};
	string toString(const ItemType type) const{
		string typeTexture;
		switch (type)
		{
		case Stick:
			typeTexture = "Stick";
			break;
		case Lever:
			typeTexture = "Lever";
			break;
		case Pipe:
			typeTexture = "Pipe";
			break;
		case Ax:
			typeTexture = "Ax";
			break;
		case Alcohol:
			typeTexture = "Alcohol";
			break;
		case Bandages:
			typeTexture = "Bandages";
			break;
		case Firstaid:
			typeTexture = "Firstaid";
			break;
		case GenericChemical:
			typeTexture = "GenericChemical";
			break;
		case AcidChemical:
			typeTexture = "AcidChemical";
			break;
		case Acid:
			typeTexture = "Acid";
			break;
		case Biocide:
			typeTexture = "Biocide";
			break;
		case PiecePuzzle:
			typeTexture = "PiecePuzzle";
			break;
		case Card:
			typeTexture = "Card";
			break;
		case Key:
			typeTexture = "Key";
			break;
		case Insulationtape:
			typeTexture = "Insulationtape";
			break;
		case Photo:
			typeTexture = "Photo";
			break;
		default:
			typeTexture = "";
			break;
		}
		return typeTexture;
	};

private:
	ItemType type_;
};