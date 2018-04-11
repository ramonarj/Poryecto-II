#include "Game.h"
#include "EntityCreator.h"

unique_ptr<Game> Game:: s_pInstance = nullptr;

Game::Game() : SDLGame("Cursed Gold 2", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	//Initialization
	initGame();

	//Se añade MenuScene
	//getResources()->getMusic(Resources::Menu)->play();
	stateMachine_.pushState(PlayState::Instance());
	//stateMachine_.pushState(MenuState::Instance());
	//stateMachine_.pushState(new LightTestState(this));

	exit_ = false;
}

Game::~Game() {
	closeGame();
}

void Game::initGame() 
{
	//Añadir las factorias de las Entidades
	addGameObjectsFactory();

	//Initializate ResourceManager
	resourceManager_ = new ResourceManager(this);

	//Añadir los assets
	addResourcesTexture();
	addResourcesMusic();
	addResourcesSoundEffects();
	addResourcesFonts();
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
		stateMachine_.currentState()->removeEntities();
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
				setFullScreen();
				break;
			}

		}

		//HandleInput de la Escena actual
		stateMachine_.currentState()->handleInput(time, event_);
	}
}

void Game::setFullScreen(){
	int flags = SDL_GetWindowFlags(window_);
	if (flags & SDL_WINDOW_FULLSCREEN) {
		SDL_SetWindowFullscreen(window_, 0);
	}
	else {
		SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
	}
}

void Game::addGameObjectsFactory()
{
	gameObjectFactory->registerType("Player", new PlayerCreator());
	gameObjectFactory->registerType("Enemy", new EnemyCreator());
	gameObjectFactory->registerType("Puerta", new DoorCreator());
	registerTypeItem();
}

void Game::addResourcesTexture()
{
	//Characters
	resourceManager_->addTexture("SpriteSheetElise", "images/SpriteSheetElise.png");
	resourceManager_->addTexture("Enemigo1", "images/Enemigo1.png");

	//Items
	resourceManager_->addTexture("Firstaid", "images/Botiquin.png");
	resourceManager_->addTexture("insulationTape", "images/cintaPrueba.png");
	resourceManager_->addTexture("Crowbar", "images/Crowbar.png");
	resourceManager_->addTexture("Stick", "images/stickPrueba.png");
	resourceManager_->addTexture("Key", "images/key.png");
	resourceManager_->addTexture("Axe", "images/Hacha.png");
	resourceManager_->addTexture("acid", "images/acido.png");

	//Inventory
	resourceManager_->addTexture("Inventory", "images/Inventario/FullscreenVersions/Inventario_Full.png");
	resourceManager_->addTexture("Chest", "images/Inventario/FullscreenVersions/Cofre_Full.png");
	resourceManager_->addTexture("Craft", "images/Inventario/FullscreenVersions/Crafting_Full.png");

	//Backgrounds
	resourceManager_->addTexture("FondoMenu", "images/Menu/FondoMenu.png");
	resourceManager_->addTexture("BgRegistro", "images/bgRegistro.png");

	//Buttons
	resourceManager_->addTexture("BotonNuevaPartida", "images/Menu/NuevaPartida.png");
	resourceManager_->addTexture("BotonExit", "images/Menu/Exit.png");

}

void Game::addResourcesMusic()
{
	resourceManager_->addMusic("Menu", "music/Menu.mp3");
	resourceManager_->addMusic("SafeRoom", "music/SafeRoom.mp3");
}

void Game::addResourcesSoundEffects()
{
	resourceManager_->addSound("InventoryOpen", "sounds/Inventory.wav");
}

void Game::addResourcesFonts()
{
	resourceManager_->addFont("ARIAL", "fonts/ARIAL.ttf", 24);
	resourceManager_->addFont("NES-Chimera", "fonts/NES-Chimera.ttf", 24);
	resourceManager_->addFont("VCR_OSD_MONO", "fonts/VCR_OSD_MONO.ttf", 21);
}

void Game::registerTypeItem() {
	gameObjectFactory->registerType("Crowbar", new ItemCreator(ItemType::CROWBAR));
	gameObjectFactory->registerType("Key", new ItemCreator(ItemType::KEY));
	gameObjectFactory->registerType("Axe", new ItemCreator(ItemType::AXE));
	gameObjectFactory->registerType("Firstaid", new ItemCreator(ItemType::FIRSTAID));
	/*gameObjectFactory->registerType("Stick", new ItemCreator(ItemType::STICK));
	gameObjectFactory->registerType("Pipe", new ItemCreator(ItemType::PIPE));
	gameObjectFactory->registerType("Alcohol", new ItemCreator(ItemType::ALCOHOL));
	gameObjectFactory->registerType("Bandages", new ItemCreator(ItemType::BANDAGES));
	gameObjectFactory->registerType("GenericChemical", new ItemCreator(ItemType::GENERICCHEMICAL));
	gameObjectFactory->registerType("AcidChemical", new ItemCreator(ItemType::ACIDCHEMICAL));
	gameObjectFactory->registerType("Acid", new ItemCreator(ItemType::ACID));
	gameObjectFactory->registerType("Biocide", new ItemCreator(ItemType::BIOCIDE));
	gameObjectFactory->registerType("Piecepuzzle", new ItemCreator(ItemType::PIECEPUZZLE));
	gameObjectFactory->registerType("Card", new ItemCreator(ItemType::CARD));
	gameObjectFactory->registerType("Insulationtape", new ItemCreator(ItemType::INSULATIONTEPE));
	gameObjectFactory->registerType("Photo", new ItemCreator(ItemType::PHOTO));*/
}