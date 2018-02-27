#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "Component.h"

/*
 *
 */
class RenderComponent : public Component{
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render(Entity* e, Uint32 time) = 0;

};

#endif /* RENDERCOMPONENT_H_ */
