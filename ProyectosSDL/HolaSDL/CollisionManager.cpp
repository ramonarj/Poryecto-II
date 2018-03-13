#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

void CollisionManager::checkPlayerTileCollision(Entity* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = layerPos.getX() / pTileLayer->getTileSize();
		y = layerPos.getY() / pTileLayer->getTileSize();

		if (pPlayer->getVelocity().getX() > 0 || pPlayer->getVelocity().getY() > 0)
		{
			tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
			tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
			tileid = tiles[tileRow + y][tileColumn + x];

			if (tileid == 0)
			{
				if (pPlayer->getVelocity().getX() > 0)
				{
					tileRow = ((pPlayer->getPosition().getY() + (pPlayer->getHeight() / 2)) / pTileLayer->getTileSize());
					tileid = tiles[tileRow + y][tileColumn + x];

					if (tileid == 0)
					{
						tileRow = (pPlayer->getPosition().getY() / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];
					}
				}

				else if (pPlayer->getVelocity().getY() > 0)
				{
					tileColumn = ((pPlayer->getPosition().getX() + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
					tileid = tiles[tileRow + y][tileColumn + x];

					if (tileid == 0)
					{
						tileColumn = (pPlayer->getPosition().getX() / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];
					}
				}
			}
		}
		else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
		{
			tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
			tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];

			if (tileid == 0)
			{
				if (pPlayer->getVelocity().getX() < 0)
				{
					tileRow = ((pPlayer->getPosition().getY() + (pPlayer->getHeight() / 2)) / pTileLayer->getTileSize());
					tileid = tiles[tileRow + y][tileColumn + x];

					if (tileid == 0)
					{
						tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];
					}
				}
				else if (pPlayer->getVelocity().getY() < 0)
				{
					tileColumn = ((pPlayer->getPosition().getX() + (pPlayer->getWidth() / 2)) / pTileLayer->getTileSize());
					tileid = tiles[tileRow + y][tileColumn + x];

					if (tileid == 0)
					{
						tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
						tileid = tiles[tileRow + y][tileColumn + x];
					}
				}
			}
		}

		if (tileid != 0)
		{
			Vector2D pos(0, 0);
			pos.setX(pPlayer->getPosition().getX() - pPlayer->getVelocity().getX());
			pos.setY(pPlayer->getPosition().getY() - pPlayer->getVelocity().getY());
			pPlayer->setPosition(pos);
		}
	}
}
