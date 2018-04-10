#pragma once
#include "Entity.h"
#include "TileLayer.h"
#include <list>
#include "Collisions.h"
#include <memory>

class CollisionManager
{
public:

	static CollisionManager* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new CollisionManager());
		return s_pInstance.get();
	}

	void checkEntityTileCollision(std::list<Entity*> characters, const
		std::vector<TileLayer*> &collisionLayers);

private:
	CollisionManager() {};
	static unique_ptr<CollisionManager> s_pInstance;
};

typedef CollisionManager CollisionManager;