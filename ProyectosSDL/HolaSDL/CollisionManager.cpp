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
				tileColumn = (((pos.getX() + width)) / tileSize);
				tileRow = ((pos.getY() + height) / tileSize);
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if (c->getVelocity().getX() > 0)
					{
						tileRow = ((pos.getY() + (height / 2)) / tileSize);
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileRow = (pos.getY() / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}

					if (tileid == 0)
					{
						if (c->getVelocity().getY() > 0)
						{
							tileColumn = ((pos.getX() + (width / 2)) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];

							if (tileid == 0)
							{
								tileColumn = (pos.getX() / tileSize);
								tileid = tiles[tileRow + y][tileColumn + x];
							}
						}
					}
				}
			}
			else if (c->getVelocity().getX() < 0 || c->getVelocity().getY() < 0)
			{
				tileColumn = pos.getX() / tileSize;
				tileRow = pos.getY() / tileSize;
				tileid = tiles[tileRow + y][tileColumn + x];

				if (tileid == 0)
				{
					if (c->getVelocity().getX() < 0)
					{
						tileRow = ((pos.getY() + (height / 2)) / tileSize);
						tileid = tiles[tileRow + y][tileColumn + x];

						if (tileid == 0)
						{
							tileRow = ((pos.getY() + height) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];
						}
					}
					if (tileid == 0)
					{
						if (c->getVelocity().getY() < 0)
						{
							tileColumn = ((pos.getX() + (width / 2)) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];

							if (tileid == 0)
							{
								tileColumn = ((pos.getX() + width) / tileSize);
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
