#include "Interactible.h"
#include "Game.h"

Interactible::Interactible(std::string message, double textX, double textY) :
	message_(message), textX_(textX), textY_(textY), display_(false), color_({255, 255, 255, 255}),
	font_(Game::Instance()->getResourceManager()->getFont("VCR_OSD_MONO")) {
	
}

void Interactible::render(Entity* e, Uint32 time) {
	if (message_ != "" && display_) {
		/*SDL_Surface* textSurface = font_->renderText(message_, color_);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);
		int textW = textSurface->w;
		int textH = textSurface->h;
		SDL_FreeSurface(textSurface);
		SDL_Rect renderQuad = { textX_ - textW / 2, textY_ - textH / 2, textW, textH };
		SDL_RenderCopy(Game::Instance()->getRenderer(), textTexture, nullptr, &renderQuad);
		SDL_DestroyTexture(textTexture);*/
		cout << message_ << endl;
	}
}