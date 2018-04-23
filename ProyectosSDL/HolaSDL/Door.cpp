#include "Door.h"
#include "Game.h"
#include "PlayState.h"
#include "MessageTrigger.h"

Door::Door(Entity* thisDoor) : player(nullptr), inventory(nullptr), compContainer(nullptr),
	compInvent(nullptr), itemKey(nullptr), doorNum_(0), numKey_(0), needKey_(false), 
	collidableDoor_(false), messageChanged_(false), thisDoor_(thisDoor) {
}


Door::~Door() {
}

void Door::interact(Entity * e)
{
	int n = 0;
	if (collidableDoor_) 
	{
		doors = (*Game::Instance()->stateMachine_.currentState()->getDoors());
		

		if (needKey_)
		{
			setNeedKey();
		}
		else
		{
			if (canTeleport())
			{
				list<Entity*>::const_iterator it = doors.begin();
				bool puertEncontrada = false;

				while (it != doors.end() && !puertEncontrada)
				{
					if (e != (*it))
					{
						Door* doorComp = (*it)->getComponent<Door>();
						if (doorNum_ == doorComp->getDoorNum() && doorComp->isCollidable())
						{
							if (doorComp->getOri() == "norte")
								player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2 - player->getWidth() / 2,
								(*it)->getPosition().getY() + (*it)->getHeight() / 10));

							else if (doorComp->getOri() == "sur")
								player->setPosition(Vector2D(((*it)->getPosition().getX() + (*it)->getWidth() / 2) - player->getWidth() / 2,
								(*it)->getPosition().getY() - player->getHeight() / 2));

							else if (doorComp->getOri() == "este")
								player->setPosition(Vector2D((*it)->getPosition().getX() - player->getWidth() / 2,
								(*it)->getPosition().getY()));

							else if (doorComp->getOri() == "oeste")
								player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2,
								(*it)->getPosition().getY()));

							puertEncontrada = true;
						}
					}
					it++;
				}
			}
		}
	}
}

void Door::load(int numero, string ori, int numKey, int needKey, int collidableDoor)
{
	doorNum_ = numero;
	ori_ = ori;
	numKey_ = numKey;
	needKey_ = needKey;
	if (needKey_)
		thisDoor_->getComponent<MessageTrigger>()->setMessage("Necesitas una llave");
	collidableDoor_ = { collidableDoor == 0 ? false : true };
}

bool Door::canTeleport()
{
	PlayerAnimationComponent* animPlayer = player->getComponent<PlayerAnimationComponent>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}

bool Door::getNeedKey()
{
	return needKey_;
}

void Door::setNeedKey()
{
	//inventory = Game::Instance()->getEntityWithComponent<Inventory>();
	compContainer = inventory->getComponent<ItemContainer>();
	//compInvent = inventory->getComponent<Inventory>();

	if (!compInvent->getKeys().empty()) {
		int i = 0;
		while (i < compInvent->getKeys().size() && needKey_)
		{
			if (compInvent->getKeys()[i]->getComponent<Key>()->getDoorId() == numKey_) {
				openDoor();
			}
			else
				i++;
		}
	}
}

void Door::openDoor()
{
	for (list<Entity*>::const_iterator it = doors.begin(); it != doors.end(); it++)
	{
		Door* doorComp = (*it)->getComponent<Door>();

		if (doorComp->getNeedKey()) {
			if (doorNum_ == doorComp->getDoorNum())
				doorComp->keyFalse();
		}
	}
}

void Door::keyFalse()
{
	needKey_ = false;
}

bool Door::isCollidable()
{
	return collidableDoor_;
}

void Door::openMessage() {
	thisDoor_->getComponent<MessageTrigger>()->setMessage("'E' para abrir", "'Square/X' para abrir", true);
}

void Door::update(Entity * e, Uint32 time) {
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();
	if (inventory == nullptr)
		inventory = Game::Instance()->getEntityWithComponent<Inventory>();
	if (compInvent == nullptr)
		compInvent = inventory->getComponent<Inventory>();

	if (needKey_ && !messageChanged_) {
		SDL_Rect playerRect = { int(player->getPosition().getX()), int(player->getPosition().getY()), int(player->getWidth()), int(player->getHeight()) };
		SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

		if (Collisions::RectRect(&playerRect, &thisRect)) {
			if (!compInvent->getKeys().empty()) {
				int i = 0;
				bool found = false;
				while (i < compInvent->getKeys().size() && !found)
				{
					if (compInvent->getKeys()[i]->getComponent<Key>()->getDoorId() == numKey_) {
						openMessage();
						found = true;
						messageChanged_ = true;
					}
					else
						i++;
				}
			}
		}
	}
}
