#include "TextNote.h"

TextNote::TextNote(Game* game_, string text) : renderer_(game_->getRenderer()), 
	font_(game_->getResourceManager()->getFont("NES-Chimera")), pos_(Vector2D(0,0)),
	color_{ 0, 0, 0, 255 } {
	textLines.push_back(text); //PROVISIONAL ------------------------------------
	/*for (int i = 0; i < textLines.size(); i++) {
		textTextures_[i] = Texture(renderer_, textLines[i], *font_, color_);
	}*/
}

TextNote::~TextNote() {
}

void TextNote::render(Entity * e, Uint32 time) {
	for (string t : textLines) {
		SDL_Surface* textSurface = font_->renderText(t, color_);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
		int textW = textSurface->w;
		int textH = textSurface->h;
		SDL_FreeSurface(textSurface);
		SDL_Rect renderRect = { pos_.getX(), pos_.getY(), textW, textH };
		SDL_RenderCopy(renderer_, textTexture, nullptr, &renderRect);
		SDL_DestroyTexture(textTexture);
	}
}
