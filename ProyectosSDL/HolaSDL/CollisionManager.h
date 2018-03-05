#pragma once
#include "Entity.h"
#include "TileLayer.h"
class CollisionManager
{
public:

	/*void checkPlayerEnemyBulletCollision(Entity* pPlayer);

	void checkPlayerEnemyCollision(Entity* pPlayer, const
		std::vector<GameObject*> &objects);

	void checkEnemyPlayerBulletCollision(const
		std::vector<GameObject*> &objects);*/

	void checkPlayerTileCollision(Entity* pPlayer, const
		std::vector<TileLayer*> &collisionLayers);
};

