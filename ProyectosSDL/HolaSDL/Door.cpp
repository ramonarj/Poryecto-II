#include "Door.h"
#include "Game.h"
#include "PlayState.h"

Door::Door() : player(nullptr), inventory(nullptr), compContainer(nullptr),
	compInvent(nullptr), itemKey(nullptr), doorNum_(0), numKey_(0), needKey_(false)
{
}


Door::~Door()
{
}

void Door::interact(Entity * e)
{
	doors = (*Game::Instance()->stateMachine_.currentState()->getDoors());
	player = PlayState::Instance()->getPlayer();

	if (needKey_)
		setNeedKey();
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
					if (doorNum_ == doorComp->getDoorNum())
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

void Door::load(int numero, string ori, int numKey, int needKey)
{
	doorNum_ = numero;
	ori_ = ori;
	numKey_ = numKey;
	if (needKey == 0)
		needKey_ = false;
	else
		needKey_ = true;
}

bool Door::canTeleport()
{
	AnimationRenderer* animPlayer = player->getComponent<AnimationRenderer>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}

void Door::setNeedKey()
{
	inventory = Game::Instance()->getEntityWithComponent<Inventory>();
	compContainer = inventory->getComponent<ItemContainer>();
	compInvent = inventory->getComponent<Inventory>();

	if (!compInvent->getKeys().empty()) {

		int i = 0;
		while (i < compInvent->getKeys().size() && needKey_)
		{
			if (compInvent->getKeys()[i]->getComponent<Key>()->getDoorId() == numKey_)
				needKey_ = false;
			else
				i++;
		}
	}
}
