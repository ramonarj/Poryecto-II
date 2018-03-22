#pragma once

#include "GameObjectFactory.h"
#include "Player.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "Resources.h"
#include "SkeletonRenderer.h"

class PlayerCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity();
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Player());
		e->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
			SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_C, SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN));
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::SpriteSheetElise),14, 6, 26, 80, true, false));
		return e;
	}
};

class EnemyCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Vector2D vel (1.0, 0.0);
		Entity* e = new Entity();
		e->setVelocity(vel);
		e->addComponent(new Enemy(vel));
		e->addComponent(new AnimationRenderer(Game::Instance()->getResources()->getImageTexture(Resources::Enemigo1), 10, 0, 10, 150, true, false));
		return e;
	}
};

class ItemCreator : public BaseCreator
{
public:
	ItemCreator(ItemType type) : type_(type) {};
	Entity* createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(chooseItemType(type_));
		e->addComponent(new ImageRenderer(Game::Instance()->getResourceManager()->getTexture(toString(type_))));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	};
	Component* chooseItemType(const ItemType type) const{
		Item* i;
		switch (type)
		{
		case STICK:
			i = new Weapon(type,toString(type));
			break;
		case LEVER:
			i = new Weapon(type, toString(type));
			break;
		case PIPE:
			i = new Weapon(type, toString(type));
			break;
		case AX:
			i = new Weapon(type, toString(type));
			break;
		case FIRSTAID:
			i = new FirstAid(toString(type));
			break;
		case INSULATIONTEPE:
			i = new InsulationTape(toString(type));
			break;
		case KEY:
			i = new Key(toString(type));
			break;
		default:
			i = new Item(type, toString(type));
			break;
		}
		
		return i;
	};
	string toString(const ItemType type) const{
		string str;
		switch (type)
		{
		case STICK:
			str = "Stick";
			break;
		case LEVER:
			str = "Lever";
			break;
		case PIPE:
			str = "Pipe";
			break;
		case AX:
			str = "Ax";
			break;
		case ALCOHOL:
			str = "Alcohol";
			break;
		case BANDAGES:
			str = "Bandages";
			break;
		case FIRSTAID:
			str = "Firstaid";
			break;
		case GENERICCHEMICAL:
			str = "GenericChemical";
			break;
		case ACIDCHEMICAL:
			str = "AcidChemical";
			break;
		case ACID:
			str = "Acid";
			break;
		case BIOCIDE:
			str = "Biocide";
			break;
		case PIECEPUZZLE:
			str = "PiecePuzzle";
			break;
		case CARD:
			str = "Card";
			break;
		case KEY:
			str = "Key";
			break;
		case INSULATIONTEPE:
			str = "Insulationtape";
			break;
		case PHOTO:
			str = "Photo";
			break;
		default:
			str = "";
			break;
		}
		return str;
	};

private:
	ItemType type_;
};

class DoorCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		return e;
	}
};