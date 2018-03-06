#ifndef FILLRECTRENDERER_H_
#define FILLRECTRENDERER_H_

#include "Component.h"
#include "Game.h"

/*
 *
 */
class FillRectRenderer : public Component {
public:
	FillRectRenderer();
	FillRectRenderer(SDL_Color color);
	virtual ~FillRectRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	SDL_Color color_;
};

#endif /* FILLRECTRENDERER_H_ */
