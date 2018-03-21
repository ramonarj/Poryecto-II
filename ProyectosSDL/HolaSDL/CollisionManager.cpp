#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

void CollisionManager::checkPlayerTileCollision(std::list<Entity*> characters, const std::vector<TileLayer*>& collisionLayers)
{
	int zoom = Camera::Instance()->getZoom();
	for (TileLayer* it : collisionLayers)
	{
		TileLayer* pTileLayer = it;
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		int tileSize = pTileLayer->getTileSize() / zoom;

		x = layerPos.getX() / tileSize;
		y = layerPos.getY() / tileSize;

		for (Entity* c : characters)
		{
			Vector2D pos(Vector2D(c->getPosition().getX() / zoom, c->getPosition().getY() / zoom));
			double width = c->getWidth() / zoom;
			double height = c->getHeight() / zoom;


			if (c->getVelocity().getX() >  0 || c->getVelocity().getY() > 0)
			{
				tileColumn = ((pos.getX() + 2* width / 3) / tileSize);
				tileRow = ((pos.getY() + 9 * height / 10) / tileSize);
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if (c->getVelocity().getX() > 0)
					{
						tileRow = ((pos.getY() + (height / 2)) / tileSize);
						tileid = tiles[tileRow + y][tileColumn + x];
					}

					if (tileid == 0)
					{
						if (c->getVelocity().getY() > 0)
						{
							tileColumn = ((pos.getX() + (width / 2)) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];

							if (tileid == 0)
							{
								tileColumn = ((pos.getX() + width / 3) / tileSize);
								tileid = tiles[tileRow + y][tileColumn + x];
							}
						}
					}
				}
			}
			else if (c->getVelocity().getX() < 0 || c->getVelocity().getY() < 0)
			{
				tileColumn = (pos.getX() + width / 3) / tileSize;
				tileRow = (pos.getY() + (height / 2)) / tileSize;
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if (c->getVelocity().getX() < 0)
					{
						tileRow = ((pos.getY() + 9 * height / 10) / tileSize);
						tileid = tiles[tileRow + y][tileColumn + x];
					}

					if (tileid == 0)
					{
						if (c->getVelocity().getY() < 0)
						{
							tileColumn = ((pos.getX() + (width / 2)) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];

							if (tileid == 0)
							{
								tileColumn = ((pos.getX() + 2 * width / 3) / tileSize);
								tileid = tiles[tileRow + y][tileColumn + x];
							}
						}
					}
				}
			}

			if (tileid != 0)
			{
				Vector2D pos(0, 0);
				pos.setX(c->getPosition().getX() - c->getVelocity().getX());
				pos.setY(c->getPosition().getY() - c->getVelocity().getY());
				c->setPosition(pos);
			}
		}
	}
}

void CollisionManager::checkPlayerDoorCollision(Entity * player, const std::list<Entity*> doors)
{
	Entity* puerta = nullptr;
	SDL_Rect playerRect{ player->getRect().x, player->getRect().y + player->getRect().h / 2, player->getRect().w, player->getRect().h };
	Player* playerComp = player->getComponent<Player>();

	//Comprueba si el personaje ha colisionado con alguna puerta
	list<Entity*>::const_iterator it = doors.begin();
	bool chocaPuerta = false;
	while (it != doors.end() && !chocaPuerta)
	{
		if (Collisions::RectRect(&playerRect, &(*it)->getRect())) {
			puerta = (*it);
			chocaPuerta = true;
			playerComp->setDoorCollision(true);

			/*if ((*it)->getOri() == "norte" && (player->getDirection().getX() == 0 && player->getDirection().getY() == 1))
				playerComp->setDoorCollision(true);
			else if ((*it)->getOri() == "sur" && (player->getDirection().getX() == 0 && player->getDirection().getY() == -1))
				playerComp->setDoorCollision(true);
			else if ((*it)->getOri() == "este" && (player->getDirection().getX() == 1 && player->getDirection().getY() == 0))
				playerComp->setDoorCollision(true);
			else if ((*it)->getOri() == "oeste" && (player->getDirection().getX() == -1 && player->getDirection().getY() == 0))
				playerComp->setDoorCollision(true);*/
		}
		else
		{
			playerComp->setDoorCollision(false);
			it++;
		}
	}

	//Si el personaje quiere hacer un teleport, se busca una puerta con el mismo numero
	list<Entity*>::const_iterator it2 = doors.begin();
	bool puertEncontrada = false;
	if (it != doors.end() && playerComp->getTeleport())
	{
		while (it2 != doors.end() && !puertEncontrada)
		{
			if ((*it2) != (*it))
			{
				if ((*it2)->getDoorNum() == (*it)->getDoorNum())
				{
					if ((*it2)->getOri() == "norte")
						player->setPosition(Vector2D((*it2)->getPosition().getX() + (*it2)->getWidth() / 2 - player->getWidth() / 2,
						(*it2)->getPosition().getY() + (*it2)->getHeight() / 10));

					else if ((*it2)->getOri() == "sur")
						player->setPosition(Vector2D(((*it2)->getPosition().getX() + (*it2)->getWidth() / 2) - player->getWidth() / 2,
						(*it2)->getPosition().getY() - player->getHeight() / 2));

					else if ((*it2)->getOri() == "este")
						player->setPosition(Vector2D((*it2)->getPosition().getX() - player->getWidth() / 2,
						(*it2)->getPosition().getY()));

					else if ((*it2)->getOri() == "oeste")
						player->setPosition(Vector2D((*it2)->getPosition().getX() + (*it2)->getWidth() / 2, 
						(*it2)->getPosition().getY()));
	
					playerComp->setTeleport(false);
					puertEncontrada = true;
				}
			}

			it2++;
		}
	}
}
