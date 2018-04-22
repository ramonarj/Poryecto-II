#include "Game.h"
#include "EntityCreator.h"
#include "SlidingPuzzle.h"

unique_ptr<Game> Game:: s_pInstance = nullptr;

Game::Game() : SDLGame("Cursed Gold 2048", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	//Initialization
	initGame();

	//Se añade MenuScene
	//getResources()->getMusic(Resources::Menu)->play();
	stateMachine_.pushState(PlayState::Instance());
	//stateMachine_.pushState(SlidingPuzzle::Instance());
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
	SDL_ShowCursor(0);
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
	gameObjectFactory->registerType("Camera", new SecurityCameraCreator());
	gameObjectFactory->registerType("Television", new TelevisionCreator());
	gameObjectFactory->registerType("Chest", new ChestCreator());
	gameObjectFactory->registerType("CraftingTable", new CraftingTableCreator());
	gameObjectFactory->registerType("Register", new RegisterCreator());
	gameObjectFactory->registerType("SRMap", new SRMapCreator());
	registerTypeItem();
}

void Game::addResourcesTexture()
{
	//Characters
	resourceManager_->addTexture("SpriteSheetElise", "images/Characters/SpriteSheetElise.png");

	resourceManager_->addTexture("Elise_Iddle", "images/Characters/Elise/Iddle_Elise.png");
	resourceManager_->addTexture("Elise_Awakening", "images/Characters/Elise/Despertar_Elise.png");
	resourceManager_->addTexture("Elise_Moving", "images/Characters/Elise/Movimiento_Elise.png");
	resourceManager_->addTexture("Elise_AttackingCrowbar", "images/Characters/Elise/AtacandoCrowbar_Elise.png");
	resourceManager_->addTexture("Elise_AttackingPipe", "images/Characters/Elise/AtacandoPipe_Elise.png");
	resourceManager_->addTexture("Elise_AttackingAxe", "images/Characters/Elise/AtacandoAxe_Elise.png");
	resourceManager_->addTexture("Elise_AttackingCrutch", "images/Characters/Elise/AtacandoCrutch_Elise.png");
	resourceManager_->addTexture("Elise_Diying", "images/Characters/Elise/Muerte_Elise.png");


	resourceManager_->addTexture("Enemigo1_Iddle", "images/Characters/Enemigo1/Enemigo1_Iddle.png");
	resourceManager_->addTexture("Enemigo1_Moving", "images/Characters/Enemigo1/Enemigo1_Moving.png");
	resourceManager_->addTexture("Enemigo1_Attacking", "images/Characters/Enemigo1/Enemigo1_Attacking.png");
	resourceManager_->addTexture("Enemigo1_Diying", "images/Characters/Enemigo1/Enemigo1_Diying.png");

	resourceManager_->addTexture("Enemigo1_ConAtaque", "images/Characters/Enemigo1/Enemigo1_ConAtaque.png");
	resourceManager_->addTexture("Enemigo2_ConAtaque", "images/Characters/Enemigo2.png");

	//Items
	resourceManager_->addTexture("Crowbar", "images/Weapons/crowbar.png");
	resourceManager_->addTexture("Stick", "images/Weapons/crutch.png");
	resourceManager_->addTexture("Axe", "images/Weapons/axe.png");
	resourceManager_->addTexture("Pipe", "images/Weapons/pipe.png");
	resourceManager_->addTexture("GenericChemical", "images/Items/chemical.png");
	resourceManager_->addTexture("AcidChemical", "images/Items/acid-chemical.png");
	resourceManager_->addTexture("Acid", "images/Items/acid.png");
	resourceManager_->addTexture("Biocide", "images/Items/biocide.png");
	resourceManager_->addTexture("Key", "images/Items/key1.png");
	resourceManager_->addTexture("Firstaid", "images/Items/medkit.png");
	resourceManager_->addTexture("insulationTape", "images/Items/ducktape.png");
	resourceManager_->addTexture("Alcohol", "images/Items/alcohol.png");
	resourceManager_->addTexture("Bandages", "images/Items/bandage.png");
	resourceManager_->addTexture("Card", "images/Items/keycard.png");
	resourceManager_->addTexture("Television", "images/Items/television.png");

	//Inventory
	resourceManager_->addTexture("Inventory", "images/Inventario/FullscreenVersions/Inventario_Full.png");
	resourceManager_->addTexture("Chest", "images/Inventario/FullscreenVersions/Cofre_Full.png");
	resourceManager_->addTexture("Craft", "images/Inventario/FullscreenVersions/Crafting_Full.png");

	//Puzzle
	resourceManager_->addTexture("SlidingPuzzle", "images/puzzle.jpg");

	//Backgrounds
	resourceManager_->addTexture("FondoMenu", "images/Menu/FondoMenu.png");
	resourceManager_->addTexture("BgRegistro", "images/bgRegistro.png");
	resourceManager_->addTexture("SRMapa1", "images/SRMap/SRMap1.png");
	resourceManager_->addTexture("SRMapa2", "images/SRMap/SRMap2.png");
	resourceManager_->addTexture("SRMapa3", "images/SRMap/SRMap3.png");

	//Buttons
	resourceManager_->addTexture("BotonNuevaPartida", "images/Menu/NuevaPartida.png");
	resourceManager_->addTexture("BotonExit", "images/Menu/Exit.png");

	//Cursors
	resourceManager_->addTexture("Cursor", "images/stickPrueba.png");
	resourceManager_->addTexture("InventoryCursor", "images/Inventario/CursorInventario.png");

	//Lighting
	resourceManager_->addTexture("PlayerLight", "images/Shadows/PlayerLight.png");
	resourceManager_->addTexture("Black", "images/Shadows/Black.png");
	resourceManager_->addTexture("PointLight", "images/Shadows/PointLight.png");
	resourceManager_->addTexture("BGtest", "images/Shadows/BGtest.png");

	//AnimationTilesheet
	resourceManager_->addTexture("SecurityCameras", "images/AnimTilesheet/TileshetCameras.png");

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
	gameObjectFactory->registerType("Photo", new ItemCreator(ItemType::PHOTO));
	gameObjectFactory->registerType("Masck", new ItemCreator(ItemType::MASCK));*/
}