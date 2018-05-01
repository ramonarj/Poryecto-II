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
#include "MessageTrigger.h"
#include "SlidingPuzzleItem.h"
#include "SavePoint.h"

class PlayerCreator : public BaseCreator
{
public:
	Entity* createEntity() const
	{
		Entity* e = new Entity();
		e->setVelocity(Vector2D(0.0, 0.0));
		e->addComponent(new Player());
		e->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
			SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_C,  SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN, SDL_SCANCODE_X, SDL_SCANCODE_0,
			SDL_SCANCODE_G, SDL_SCANCODE_H));

		e->addComponent(new ControllerInputComponent());
		
		//e->addComponent(new AnimationRenderer(Game::Instance()->getResourceManager()->getTexture("SpriteSheetElise"),14, 6, 26, 80, true, false));
		e->addComponent(new PlayerAnimationComponent(Game::Instance()->getResourceManager()->getTexture("Elise_Iddle"), Game::Instance()->getResourceManager()->getTexture("Elise_Moving"),
			Game::Instance()->getResourceManager()->getTexture("Elise_AttackingCrowbar"), Game::Instance()->getResourceManager()->getTexture("Elise_AttackingPipe"), Game::Instance()->getResourceManager()->getTexture("Elise_AttackingCrutch"),
			Game::Instance()->getResourceManager()->getTexture("Elise_AttackingAxe"), Game::Instance()->getResourceManager()->getTexture("Elise_Diying"), Game::Instance()->getResourceManager()->getTexture("Elise_Awakening"),
			80, 2, 12, 6, 6, 6));
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
		e->addComponent(new MessageTrigger("'E' para recoger", "Square/X para recoger"));
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
			i = new Weapon(type, itemTypetoString(type), "Has recogido una tubería");
			break;
		case AXE:
			i = new Weapon(type, itemTypetoString(type), "Has recogido un hacha");
			break;
		case FIRSTAID:
			//i = new Movable();	//	DEBUG
			//i = new FirstAid(itemTypetoString(type), "Has recogido un botiquín");
			i = new SlidingPuzzleItem();	//	DEGUG
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
		e->addComponent(new MessageTrigger("'E' para abrir", "'Square/X' para abrir"));
		e->addComponent(new Door(e));
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
		e->addComponent(new MessageTrigger("'E' para leer el registro", "'Square/X' para leer el registro"));
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
		e->addComponent(new MessageTrigger("'E' para abrir el contenedor", "'Square/X' para abrir el contenedor"));
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
		e->addComponent(new MessageTrigger("'E' para usar la mesa de trabajo", "'Square/X' para usar la mesa de trabajo"));
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
		e->addComponent(new MessageTrigger("'E' para ver el mapa", "'Square/X' para ver el mapa"));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}
};

class SlidingPuzzleItemCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new SlidingPuzzleItem());
		e->addComponent(new MessageTrigger("'E' para ver el puzzle", "'Square/X' para ver el puzzle"));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}

};

class SavePointCreator : public BaseCreator
{
public:
	Entity * createEntity() const
	{
		Entity* e = new Entity();
		e->addComponent(new SavePoint());
		e->addComponent(new MessageTrigger("'E' para dormir y Guardar Partida", "'Square/X' para dormir y Guardar Partida"));
		Game::Instance()->stateMachine_.currentState()->getInteractibles()->push_back(e);
		return e;
	}

};