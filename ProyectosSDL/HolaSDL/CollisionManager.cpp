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

	list<Entity*>::const_iterator it = doors.begin();
	bool chocaPuerta = false;
	while (it != doors.end() && !chocaPuerta)
	{
		if (Collisions::RectRect(&playerRect, &(*it)->getRect())) {
			puerta = (*it);
			chocaPuerta = true;

			playerComp->setDoorCollision(true);
		}
		else
		{
			playerComp->setDoorCollision(false);
			it++;
		}
	}

	it = doors.begin();
	bool puertEncontrada = false;

	if (puerta != nullptr && playerComp->getTeleport())
	{
		while (it != doors.end() && !puertEncontrada)
		{
			if ((*it) != puerta)
			{
				if ((*it)->getDoorNum() == puerta->getDoorNum())
				{
					if ((*it)->getOri() == "norte")
						player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2 - player->getWidth() / 2,
						(*it)->getPosition().getY() + player->getHeight() / 2));

					else if ((*it)->getOri() == "sur")
						player->setPosition(Vector2D(((*it)->getPosition().getX() + (*it)->getWidth() / 2) - player->getWidth() / 2,
						(*it)->getPosition().getY() - player->getHeight()));

					else if ((*it)->getOri() == "este")
						player->setPosition(Vector2D((*it)->getPosition().getX() - player->getWidth(),
						(*it)->getPosition().getY()));

					else if ((*it)->getOri() == "oeste")
						player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2, 
						(*it)->getPosition().getY()));
	
					playerComp->setTeleport(false);
					puertEncontrada = true;
				}
			}

			it++;
		}
	}
}
