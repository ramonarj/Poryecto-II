#include "Game.h"

Game::Game() : SDLGame("Game Name", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

Game::~Game() {
	closeGame();
}

void Game::initGame() 
{
	//GameObject* player = new GameObject(this);
	//actors_.push_back(new GameObject* e);
	Player* playerComp = new Player(2,2);
	Enemy* enemyComp = new Enemy(playerComp);
}

void Game::closeGame() {
	//Aqui van los deletes
}

void Game::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::stop() {
	exit_ = true;
}

void Game::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			exit_ = true;

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE: //Pressing Escape will close the game
				exit_ = true;
				break;

			case SDLK_f: // Pressing f to toggle fullscreen
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				}
				else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}

		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void Game::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void Game::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x555555FF)); //Color de fondo

	SDL_RenderClear(getRenderer()); //Limpia el render

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

