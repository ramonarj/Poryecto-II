#include "Door.h"
#include "Game.h"
#include "PlayState.h"

Door::Door() : player(nullptr)
{
}


Door::~Door()
{
}

void Door::interact(Entity * e)
{
	doors = (*Game::Instance()->stateMachine_.currentState()->getDoors());
	player = PlayState::Instance()->getPlayer();
	AnimationRenderer* animPlayer = player->getComponent<AnimationRenderer>();

	bool canTeleport = false;

	if ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1))
		canTeleport = true;
	
	if (canTeleport)
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

void Door::load(int numero, string ori)
{
	doorNum_ = numero;
	ori_ = ori;
}
