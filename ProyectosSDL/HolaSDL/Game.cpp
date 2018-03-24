#include "Game.h"
#include "EntityCreator.h"

unique_ptr<Game> Game:: s_pInstance = nullptr;

Game::Game() : SDLGame("Cursed Gold 2", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	//Initialization
	initGame();

	//Se añade MenuScene
	//getResources()->getMusic(Resources::Menu)->play();
	//stateMachine_.pushState(PlayState::Instance());
	stateMachine_.pushState(MenuState::Instance());

	exit_ = false;
}

Game::~Game() {
	closeGame();
}

void Game::initGame() 
{
	gameObjectFactory->registerType("Player", new PlayerCreator());
	gameObjectFactory->registerType("Enemy", new EnemyCreator());
	gameObjectFactory->registerType("Puerta", new DoorCreator());
	registerTypeItem();

	//Initializate ResourceManager
	resourceManager_ = new ResourceManager(this);

	addResourcesTexture();
	addResourcesMusic();
	addResourcesSoundEffects();
}

void Game::closeGame() {
	//Aqui van los deletes
}

void Game::start() {

	stateMachine_.currentState()->startState();

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

void Game::addResourcesTexture()
{
	//Characters
	resourceManager_->addTexture("SpriteSheetElise", "images/SpriteSheetElise.png");
	resourceManager_->addTexture("Enemigo1", "images/Enemigo1.png");

	//Items
	resourceManager_->addTexture("PruebaMedicKit", "images/Spray.png");
	resourceManager_->addTexture("Crowbar", "images/Crowbar.png");
	resourceManager_->addTexture("Stick", "images/stickPrueba.png");
	resourceManager_->addTexture("Key", "images/key.png");

	//Inventory
	resourceManager_->addTexture("Inventory", "images/Inventario/FullscreenVersions/Inventario_Full.png");
	resourceManager_->addTexture("Chest", "images/Inventario/FullscreenVersions/Cofre_Full.png");

	//Backgrounds
	resourceManager_->addTexture("FondoMenu", "images/Menu/FondoMenu.png");

	//Buttons
	resourceManager_->addTexture("BotonNuevaPartida", "images/Menu/NuevaPartida.png");
	resourceManager_->addTexture("BotonExit", "images/Menu/Exit.png");

}

void Game::addResourcesMusic()
{
}

void Game::addResourcesSoundEffects()
{
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

void Game::registerTypeItem() {
	gameObjectFactory->registerType("Crowbar", new ItemCreator(ItemType::CROWBAR));
	gameObjectFactory->registerType("Key", new ItemCreator(ItemType::KEY));
	/*gameObjectFactory->registerType("Stick", new ItemCreator(ItemType::STICK));
	gameObjectFactory->registerType("Pipe", new ItemCreator(ItemType::PIPE));
	gameObjectFactory->registerType("Ax", new ItemCreator(ItemType::AX));
	gameObjectFactory->registerType("Alcohol", new ItemCreator(ItemType::ALCOHOL));
	gameObjectFactory->registerType("Bandages", new ItemCreator(ItemType::BANDAGES));
	gameObjectFactory->registerType("Firtsaid", new ItemCreator(ItemType::FIRSTAID));
	gameObjectFactory->registerType("GenericChemical", new ItemCreator(ItemType::GENERICCHEMICAL));
	gameObjectFactory->registerType("AcidChemical", new ItemCreator(ItemType::ACIDCHEMICAL));
	gameObjectFactory->registerType("Acid", new ItemCreator(ItemType::ACID));
	gameObjectFactory->registerType("Biocide", new ItemCreator(ItemType::BIOCIDE));
	gameObjectFactory->registerType("Piecepuzzle", new ItemCreator(ItemType::PIECEPUZZLE));
	gameObjectFactory->registerType("Card", new ItemCreator(ItemType::CARD));
	gameObjectFactory->registerType("Insulationtape", new ItemCreator(ItemType::INSULATIONTEPE));
	gameObjectFactory->registerType("Photo", new ItemCreator(ItemType::PHOTO));*/
}