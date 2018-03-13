#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

void CollisionManager::checkPlayerTileCollision(std::list<Entity*> characters, const std::vector<TileLayer*>& collisionLayers)
{
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = Camera::Instance()->getPosition().getX() / pTileLayer->getTileSize();
		y = Camera::Instance()->getPosition().getY() / pTileLayer->getTileSize();

		for (list<Entity*>::const_iterator c = characters.begin(); c != characters.end(); c++)
		{
			if ((*c)->getVelocity().getX() > 0 || (*c)->getVelocity().getY() > 0)
			{
				tileColumn = (((*c)->getPosition().getX() + (*c)->getWidth()) / pTileLayer->getTileSize());
				tileRow = (((*c)->getPosition().getY() + (*c)->getHeight()) / pTileLayer->getTileSize());
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if ((*c)->getVelocity().getX() > 0)
					{
						tileRow = (((*c)->getPosition().getY() + ((*c)->getHeight() / 2)) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileRow = ((*c)->getPosition().getY() / pTileLayer->getTileSize());
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}

					else if ((*c)->getVelocity().getY() > 0)
					{
						tileColumn = (((*c)->getPosition().getX() + ((*c)->getWidth() / 2)) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileColumn = ((*c)->getPosition().getX() / pTileLayer->getTileSize());
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}
				}
			}
			else if ((*c)->getVelocity().getX() < 0 || (*c)->getVelocity().getY() < 0)
			{
				tileColumn = (*c)->getPosition().getX() / pTileLayer->getTileSize();
				tileRow = (*c)->getPosition().getY() / pTileLayer->getTileSize();
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if ((*c)->getVelocity().getX() < 0)
					{
						tileRow = (((*c)->getPosition().getY() + ((*c)->getHeight() / 2)) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileRow = (((*c)->getPosition().getY() + (*c)->getHeight()) / pTileLayer->getTileSize());
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}
					else if ((*c)->getVelocity().getY() < 0)
					{
						tileColumn = (((*c)->getPosition().getX() + ((*c)->getWidth() / 2)) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileColumn = (((*c)->getPosition().getX() + (*c)->getWidth()) / pTileLayer->getTileSize());
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}
				}
			}

			if (tileid != 0)
			{
				Vector2D pos(0, 0);
				pos.setX((*c)->getPosition().getX() - (*c)->getVelocity().getX());
				pos.setY((*c)->getPosition().getY() - (*c)->getVelocity().getY());
				(*c)->setPosition(pos);
			}
		}
	}
}
