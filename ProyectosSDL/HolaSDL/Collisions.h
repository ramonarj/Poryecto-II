#ifndef SRC_SIMPLEENGINE_BASE_COLLISIONS_H_
#define SRC_SIMPLEENGINE_BASE_COLLISIONS_H_

#include "Vector2D.h"
#include "GameObject.h"

/*
*
*/
class Collisions {
public:
	Collisions();
	virtual ~Collisions();

	const static int s_buffer = 4;
	static bool RectRect(SDL_Rect* A, SDL_Rect* B);
};

#endif /* SRC_SIMPLEENGINE_BASE_COLLISIONS_H_ */
