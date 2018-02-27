#include "Game.h"

Game::Game() : SDLGame("Cursed Gold 2", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

Game::~Game() {
	closeGame();
}

void Game::initGame() 
{
	//Jugador
	Entity* player = new Entity(this, 2, 2);
	player->addLogicComponent(new Player(5));
	actors_.push_back(player);

	//Enemigo
	Entity* enemy = new Entity(this, 20, 10);
	enemy->addLogicComponent(new Enemy(player, 2));
	actors_.push_back(enemy);
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

		for (Entity* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void Game::update(Uint32 time) {
	for (Entity* o : actors_) {
		o->update(time);
	}
}

void Game::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x555555FF)); //Color de fondo

	SDL_RenderClear(getRenderer()); //Limpia el render

	for (Entity* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

