#pragma once
#include "Texture.h"
#include "Vector2D.h"

class Light {
public:
	Light(Texture* texture, int x, int y);
	~Light();
	Texture* getTexture() { return texture_; };
	Vector2D getPos() { return pos_; };

private:
	Texture* texture_;
	Vector2D pos_;
};

