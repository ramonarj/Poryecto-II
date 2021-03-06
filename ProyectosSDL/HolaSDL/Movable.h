#pragma once

#include "checkML.h"
#include "Component.h"
#include "Entity.h"
#include "Collisions.h"

class Movable : public Component
{
public:
	Movable();
	Movable(Entity* player);
	~Movable();
	virtual void update(Entity* e, Uint32 time) ;
	void addPlayer(Entity* player) { this->player_ = player; };
	
	//empujas los objetos 
protected:
	Entity* player_;
	bool firstCollision = true;
	Vector2D movabledir = { 0.0 , 0.0 };
	Vector2D lastVel = { 0.0, 0.0 };
};

