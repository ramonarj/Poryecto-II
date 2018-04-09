#include "CollisionManager.h"

unique_ptr<CollisionManager> CollisionManager::s_pInstance = nullptr;

void CollisionManager::checkPlayerTileCollision(std::list<Entity*> characters, const std::vector<TileLayer*>& collisionLayers)
{
	for (TileLayer* it : collisionLayers)
	{
		TileLayer* pTileLayer = it;
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		int tileSize = pTileLayer->getTileSize();

		x = layerPos.getX() / tileSize;
		y = layerPos.getY() / tileSize;

		for (Entity* c : characters)
		{
			Vector2D pos(Vector2D(c->getPosition().getX(), c->getPosition().getY()));
			double width = c->getWidth();
			double height = c->getHeight();


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
						}
					}
				}
			}
			else if (c->getVelocity().getX() < 0 || c->getVelocity().getY() < 0)
			{
				tileColumn = (pos.getX() + width / 2) / tileSize;
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
							tileColumn = ((pos.getX() + 2 * width / 3) / tileSize);
							tileid = tiles[tileRow + y][tileColumn + x];
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

				if (it->getTilesetByID(tileid).name == "Puertas")
				{
					if (tileid == 829 || tileid == 830)
					{
						tiles[tileRow + y][tileColumn + x] = -1;
						if (tileid == 829)
						{
							tiles[tileRow + y][tileColumn + x + 1] = -1;
							tiles[tileRow + y + 1][tileColumn + x + 1] = -1;
						}
						else
						{
							tiles[tileRow + y][tileColumn + x - 1] = -1;
							tiles[tileRow + y + 1][tileColumn + x - 1] = -1;
						}
						tiles[tileRow + y + 1][tileColumn + x] = -1;
					}
				}

				it->setTileIDs(tiles);
			}
		}
	}
}
