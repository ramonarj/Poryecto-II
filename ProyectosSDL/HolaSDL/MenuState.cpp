#include "MenuState.h"
#include "Game.h"

MenuState* MenuState::s_pInstance = 0;

MenuState::MenuState() : GameState() { //Constructora de nueva partida


}


MenuState::~MenuState() {

}

void MenuState::update(Uint32 time)
{
	GameState::update(time);
}

void MenuState::render(Uint32 time)
{
	//SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x2222222FF)); //Color de fondo
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());


}

void MenuState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_RETURN:
			//Cambiar a PlayState
			break;
		}
	}
		

	
}
