#pragma once
#include "Entity.h"
#include "TileLayer.h"
#include <list>
#include "Collisions.h"

class CollisionManager
{
public:

	static CollisionManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CollisionManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	//CollisionManager();
	/*void checkPlayerEnemyBulletCollision(Entity* pPlayer);

	void checkPlayerEnemyCollision(Entity* pPlayer, const
		std::vector<GameObject*> &objects);

	void checkEnemyPlayerBulletCollision(const
		std::vector<GameObject*> &objects);*/

	void checkPlayerTileCollision(std::list<Entity*> characters, const
		std::vector<TileLayer*> &collisionLayers);

	void checkPlayerDoorCollision(Entity* player,
		const std::list<Entity*> doors);

private:
	CollisionManager() {};
	static CollisionManager* s_pInstance;
};

typedef CollisionManager CollisionManager;