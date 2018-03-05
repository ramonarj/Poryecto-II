#ifndef SKELETONTENDERER_H_
#define SKELETONTENDERER_H_

#include "Component.h"

class SkeletonRendered : public Component {
public:
	SkeletonRendered();
	SkeletonRendered(SDL_Color color);
	virtual ~SkeletonRendered();
	void render(GameObject *o, Uint32 time);
private:
	SDL_Color color_;

};

#endif /* SKELETONTENDERER_H_ */
