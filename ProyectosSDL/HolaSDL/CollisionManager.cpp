#include "CollisionManager.h"

unique_ptr<CollisionManager> CollisionManager::s_pInstance = nullptr;

void CollisionManager::checkEntityTileCollision(std::list<Entity*> entity, const std::vector<TileLayer*>& collisionLayers)
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

		for (Entity* c : entity)
		{
			if (!c->isStatic() && (c->getVelocity().getX() != 0 || c->getVelocity().getY() != 0))
			{
				Vector2D pos(Vector2D(c->getPosition().getX(), c->getPosition().getY()));
				double width = c->getWidth();
				double height = c->getHeight();


				if (c->getVelocity().getX() > 0 || c->getVelocity().getY() > 0)
				{
					tileColumn = ((pos.getX() + 2 * width / 3) / tileSize);
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

					if (tileid != 0) {
						if (c->getVelocity().getX() > 0) c->setSideCollision(1);
						else c->setSideCollision(2);
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
					if (tileid != 0) {
						if (c->getVelocity().getX() < 0) c->setSideCollision(3);
						else c->setSideCollision(0);
					}
				}

				if (tileid != 0)
				{
					Vector2D pos(0, 0);
					Vector2D vel(0, 0);
					pos.setX(c->getPosition().getX() - c->getVelocity().getX());
					pos.setY(c->getPosition().getY() - c->getVelocity().getY());
					if (c->getComponent<Character>() == nullptr || c->getComponent<Character>()->getKnockBack())
						c->setVelocity(vel);
					c->setPosition(pos);
				}
			}
		}
	}
}
