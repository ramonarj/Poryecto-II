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
};

#endif /* PHYSICSCOMPONENT_H_ */