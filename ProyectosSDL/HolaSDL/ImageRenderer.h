#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "Component.h"
#include "Entity.h"

/*
 *
 */
class ImageRenderer: public Component {
public:
	ImageRenderer(Texture* image);
	virtual ~ImageRenderer();
	virtual void render(Entity* o, Uint32 time);
private:
	Texture* image_;
};

#endif /* IMAGERENDERER_H_ */
