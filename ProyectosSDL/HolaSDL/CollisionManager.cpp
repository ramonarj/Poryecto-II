#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

void CollisionManager::checkPlayerTileCollision(Entity* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
	for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
	{
		vector<Vector2D> dir(4);
		dir[0].set(-1, 0); dir[1].set(1, 0); dir[2].set(0, 1); dir[3].set(0, -1);
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerPos = pTileLayer->getPosition();

		int x, y, tileColumn, tileRow, tileid = 0;

		x = layerPos.getX() / pTileLayer->getTileSize();
		y = layerPos.getY() / pTileLayer->getTileSize();

		if (pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
		{
			tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
			tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
			tileid = tiles[tileRow + y][tileColumn + x];
		}
		else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
		{
			tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
			tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
			tileid = tiles[tileRow + y][tileColumn + x];
		}

		if (tileid != 0)
		{
			Vector2D velocity(pPlayer->getVelocity());
			velocity.setX(-velocity.getX());
			velocity.setY(-velocity.getY());
			pPlayer->setVelocity(velocity);
			pPlayer->getComponent<Player>()->move(pPlayer);
			/*Vector2D velocity(0, 0);
			pPlayer->setVelocity(velocity);*/
		}
	}
}
