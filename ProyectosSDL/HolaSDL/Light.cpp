#include "Light.h"

Light::Light(Texture* texture, int x, int y) : texture_(texture), pos_(x, y) {
	SDL_SetTextureBlendMode(texture_->getSdlTexture(), SDL_BLENDMODE_ADD);
}

Light::~Light() {
}
