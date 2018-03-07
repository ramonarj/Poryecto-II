#pragma once
#include "Entity.h"
#include "TileLayer.h"
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

	void checkPlayerTileCollision(Entity* pPlayer, const
		std::vector<TileLayer*> &collisionLayers);
private:
	CollisionManager() {};
	static CollisionManager* s_pInstance;
};

typedef CollisionManager CollisionManager;