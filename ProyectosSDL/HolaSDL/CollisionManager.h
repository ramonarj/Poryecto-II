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
			s_pInstance = new CollisionManager();

		return s_pInstance;
	}

	void checkPlayerTileCollision(std::list<Entity*> characters, const
		std::vector<TileLayer*> &collisionLayers);

private:
	CollisionManager() {};
	static CollisionManager* s_pInstance;
};

typedef CollisionManager CollisionManager;