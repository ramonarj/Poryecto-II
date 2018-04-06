#include "MenuState.h"
#include "Game.h"

unique_ptr<MenuState> MenuState::s_pInstance = nullptr;

MenuState::MenuState() : GameState(), pRenderer(nullptr), resource(nullptr), width(0), height(0) { //Constructora de nueva partida


}


MenuState::~MenuState() {

}

void MenuState::startState()
{
	Game::Instance()->getResourceManager()->getMusic("Menu")->play();
}



void MenuState::update(Uint32 time)
{
	GameState::update(time);
}

void MenuState::render(Uint32 time)
{
	pRenderer = Game::Instance()->getRenderer();
	resource = Game::Instance()->getResourceManager();
	width = Game::Instance()->getWindowWidth();
	height = Game::Instance()->getWindowHeight();

	destRect.push_back({ 0, 0, (int)width, (int)height });
	destRect.push_back({ (int)(width / 5), (int)(2 * height / 3), (int)(width / 4), (int)(height / 4) });
	destRect.push_back({ (int)(2.7* width / 5), (int)(2 * height / 3), (int)(width / 4), (int)(height / 4) });

	SDL_RenderClear(pRenderer);

	resource->getTexture("FondoMenu")->render(pRenderer, destRect[0]);
	resource->getTexture("BotonNuevaPartida")->render(pRenderer, destRect[1]);
	resource->getTexture("BotonExit")->render(pRenderer, destRect[2]);

	SDL_RenderPresent(pRenderer);
}

void MenuState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
	SDL_Point point = { event.button.x, event.button.y };

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_RETURN:
			{
				Game::Instance()->getStateMachine()->pushState(PlayState::Instance());
				PlayState::Instance()->startState();
				break;
			}
		}
	}

	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (SDL_PointInRect(&point, &destRect[1]))
		{
			Game::Instance()->getStateMachine()->pushState(PlayState::Instance());
			PlayState::Instance()->startState();
		}
		else if (SDL_PointInRect(&point, &destRect[2]))
		{
			Game::Instance()->stop();
		}
	}
}
