#pragma once

#include "GameObjectFactory.h"
#include "Player.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "AnimationRenderObject.h"
#include "Resources.h"
#include "SkeletonRenderer.h"
#include "Door.h"
#include "Movable.h"
#include "SecurityCamera.h"
#include "Register.h"
#include "ChestObject.h"
#include "CraftingTable.h"
#include "SkeletonRenderer.h"
#include "SRMap.h"

class PlayerCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity();
		e->setVelocity(Vector2D(1.0, 0.0));
		e->addComponent(new Player());
		e->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
			SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_C,  SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN, SDL_SCANCODE_X, SDL_SCANCODE_0));

		e->addComponent(new ControllerInputComponent());
		
		e->addComponent(new AnimationRenderer(Game::Instance()->getResourceManager()->getTexture("SpriteSheetElise"),14, 6, 26, 80, true, false));
		//Game::Instance()->stateMachine_.currentState()->getCharacters()->push_back(e);
		return e;
	}
};

class EnemyCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		//Vector2D vel (1.0, 0.0);
		Entity* e = new Entity();
		e->addComponent(new Enemy());
		//Game::Instance()->stateMachine_.currentState()->getCharacters()->push_back(e);
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
		//LOS OBJETOS VAN CON ANIMACION PARA OBJETOS ESTATICOS
		e->addComponent(new AnimationRenderObject(Game::Instance()->getResourceManager()->getTexture(itemTypetoString(type_)),400,false,false,true));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	};
	Component* chooseItemType(const ItemType type) const{
		Component* i;
		switch (type)
		{
		case STICK:
			i = new Weapon(type, itemTypetoString(type), "Has recogido una muleta");
			break;
		case CROWBAR:
			i = new Weapon(type, itemTypetoString(type), "Has recogido una palanca");
			break;
		case PIPE:
			i = new Weapon(type, itemTypetoString(type), "Has recogido una tuber�a");
			break;
		case AXE:
			i = new Weapon(type, itemTypetoString(type), "Has recogido un hacha");
			break;
		case FIRSTAID:
			i = new Movable();	//	DEBUG
			//i = new FirstAid(itemTypetoString(type), "Has recogido un botiqu�n");
			break;
		case INSULATIONTEPE:
			i = new InsulationTape(itemTypetoString(type), "Has recogido cinta aislante");
			break;
		case KEY:
			i = new Key(itemTypetoString(type), "Has recogido una llave");
			break;
		default:
			i = new Item(type, itemTypetoString(type));
			break;
		}
		
		return i;
	};
	string itemTypetoString(const ItemType type) const{
		string str;
		switch (type)
		{
		case STICK:
			str = "Stick";
			break;
		case CROWBAR:
			str = "Crowbar";
			break;
		case PIPE:
			str = "Pipe";
			break;
		case AXE:
			str = "Axe";
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
			str = "insulationTape";
			break;
		case PHOTO:
			str = "Photo";
			break;
		case MASK:
			str = "Mask";
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
		e->addComponent(new Door());
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};

class MovableCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new Movable());
		Game::Instance()->stateMachine_.currentState()->getStage()->push_back(e);
		return e;
	}
};

class SecurityCameraCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new SecurityCamera());
		e->addComponent(new AnimationRenderObject(Game::Instance()->getResourceManager()->getTexture("SecurityCameras"), 500, false, true, true));
		return e;
	}
};

class TelevisionCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new AnimationRenderObject(Game::Instance()->getResourceManager()->getTexture("Television"), 100, true, true, 4));
		return e;
	}
};

class RegisterCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new Register());
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};

class ChestCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		//e->addComponent(new ImageRenderer(Game::Instance()->getResourceManager()->getTexture("Axe")));
		e->addComponent(new ChestObject());
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};

class CraftingTableCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		//e->addComponent(new ImageRenderer(Game::Instance()->getResourceManager()->getTexture("Axe")));
		e->addComponent(new CraftingTable());
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};

class SRMapCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new SRMap());
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};