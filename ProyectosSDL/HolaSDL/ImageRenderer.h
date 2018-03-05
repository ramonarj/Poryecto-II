#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "Component.h"

/*
 *
 */
class ImageRenderer: public Component {
public:
	ImageRenderer(Texture* image);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	Texture* image_;
};

#endif /* IMAGERENDERER_H_ */
