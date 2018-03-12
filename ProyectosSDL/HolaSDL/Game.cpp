#include "Game.h"
#include "EntityCreator.h"

Game* Game::s_pInstance = 0;

Game::Game() : SDLGame("Cursed Gold 2", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	//Initialization
	initGame();

	//Se añade PlayScene
	stateMachine_.pushState(PlayState::Instance());

	exit_ = false;
}

Game::~Game() {
	closeGame();
}

void Game::initGame() 
{
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("Item", new ItemCreator(ItemType::Lever));
	

	//Initializate ResourceManager
	resourceManager_ = new ResourceManager(this);

	//Load Resources
	resourceManager_->addTexture("Inventory", "images/Inventory.png");
	resourceManager_->addTexture("Lever", "images/Crowbar.png");

	resourceManager_->addMusic("SafeRoom", "music/SafeRoom.mp3");
	//resourceManager_->getMusic("SafeRoom")->play();
	
}

void Game::closeGame() {
	//Aqui van los deletes
}

void Game::start() {

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("levels/Mapa.tmx");

	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		stateMachine_.currentState()->update(startTime);
		stateMachine_.currentState()->render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::stop() {
	exit_ = true;
}

void Game::handleInput(Uint32 time) {
	SDL_Event event_;
	while (SDL_PollEvent(&event_)) {
		if (event_.type == SDL_QUIT)
			exit_ = true;

		if (event_.type == SDL_KEYDOWN) {
			switch (event_.key.keysym.sym) {

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

		//HandleInput de la Escena actual
		stateMachine_.currentState()->handleInput(time, event_);
	}
}

//void Game::update(Uint32 time) {
//	for (Entity* o : actors_) {
//		o->update(time);
//	}
//}

//void Game::render(Uint32 time) {
//	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x555555FF)); //Color de fondo
//
//	SDL_RenderClear(getRenderer()); //Limpia el render
//
//	for (Entity* o : actors_) {
//		o->render(time);
//	}
//
//	SDL_RenderPresent(getRenderer());
//}

