#include "MessageRenderer.h"
#include "Game.h"
MessageRenderer::MessageRenderer() : display_(false), color_({ 255, 255, 255, 255 }),
font_(Game::Instance()->getResourceManager()->getFont("VCR_OSD_MONO")) {
}
MessageRenderer::~MessageRenderer() {
}
void MessageRenderer::display(std::string message, double textX, double textY) {
	message_ = message;
	textX_ = textX;
	textY_ = textY;
	setDisplaying(true);
}
void MessageRenderer::render(Entity * e, Uint32 time) {
	if (message_ != "" && display_) {
		SDL_Surface* textSurface = font_->renderText(message_, color_);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);
		int textW = textSurface->w;
		int textH = textSurface->h;
		SDL_FreeSurface(textSurface);
		SDL_Rect renderQuad = { (textX_ - textW / 2) - Camera::Instance()->getPosition().getX(), (textY_ - textH / 2) - Camera::Instance()->getPosition().getY(), textW, textH };
		SDL_RenderCopy(Game::Instance()->getRenderer(), textTexture, nullptr, &renderQuad);
		SDL_DestroyTexture(textTexture);
		//cout << message_ << endl;
	}
}