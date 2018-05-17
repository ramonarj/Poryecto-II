#include "Button.h"
#include "Game.h"

Button::Button(CallBackOnClick* callBack, Texture* texture, Vector2D pos) : Component(), cbOnClick(callBack), texture_(texture) {
	rect.h = texture_->getHeight();
	rect.w = texture_->getWidth();
	rect.x = pos.getX();
	rect.y = pos.getY();
}

Button::~Button() {
}

void Button::render(Entity* o, Uint32 time) {
	texture_->render(Game::Instance()->getRenderer(), rect);
}

void Button::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		if (mouseX >= rect.x && mouseX <= (rect.x + rect.w) && mouseY >= rect.y && mouseY <= (rect.y + rect.h)) {
			cbOnClick(Game::Instance());
		}
	}
}