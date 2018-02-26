#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include "Component.h"
#include "GameObject.h"

/*
 *
 */
class PhysicsComponent : public Component{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update(GameObject* o, Uint32 time) = 0;
};

#endif /* PHYSICSCOMPONENT_H_ */