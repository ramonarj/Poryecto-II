#include "Game.h"
#include "EntityCreator.h"
#include "SlidingPuzzle.h"
#include "OrderPuzzle.h"
#include "KeypadState.h"



unique_ptr<Game> Game:: s_pInstance = nullptr;

Game::Game() : SDLGame("Cursed Gold 2248: Pirate's Weird & Kinky Revenge", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	//Initialization
	initGame();

	//Se añade MenuScene
	//getResources()->getMusic(Resources::MENU)->play();
	//getResourceManager()->getMusic("Menu")->play();
	//getResourceManager()->getSound("InventorySound")->play();
	//stateMachine_.pushState(PlayState::Instance());
	//stateMachine_.pushState(KeypadState::Instance());
	//stateMachine_.pushState(KeypadState::Instance());
	//stateMachine_.pushState(OrderPuzzle::Instance());
	//stateMachine_.pushState(SlidingPuzzle::Instance());
	stateMachine_.pushState(MenuState::Instance());
	//stateMachine_.pushState(new LightTestState(this));

	stateMachine_.pushStateTick();
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
	delete resourceManager_;
	//delete gameObjectFactory;
}

void Game::start() {

	stateMachine_.currentState()->startState();

	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		stateMachine_.currentState()->saveToFile();
		stateMachine_.currentState()->loadToFile();
		stateMachine_.currentState()->update(startTime);
		stateMachine_.currentState()->render(startTime);
		stateMachine_.currentState()->removeEntities();
		stateMachine_.changeStateTick();
		if (stateMachine_.pushStateTick())
			stateMachine_.currentState()->startState();
		if (stateMachine_.getStatesToPop() >= 1) {
			for (int i = 0; i < stateMachine_.getStatesToPop(); i++)
			{
				stateMachine_.popState();
			}
		}

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

			//case SDLK_ESCAPE: //Pressing Escape will close the game
			//	exit_ = true;
			//	break;

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
	gameObjectFactory->registerType("SavePoint", new SavePointCreator());
	gameObjectFactory->registerType("Light", new LightCreator());
	gameObjectFactory->registerType("Code", new CodeCreator());
	gameObjectFactory->registerType("Countdown", new CountdownCreator());
	gameObjectFactory->registerType("MessageInteractible", new MessageInteractibleCreator());
	gameObjectFactory->registerType("Slide", new SlideCreator());
	gameObjectFactory->registerType("Order", new OrderCreator());
	gameObjectFactory->registerType("CarnePuaj", new CarnePuajCreator());
	registerTypeItem();
}

void Game::addResourcesTexture()
{
	//Characters
	resourceManager_->addTexture("SpriteSheetElise", "images/Characters/SpriteSheetElise.png");

	resourceManager_->addTexture("Elise_Iddle", "images/Characters/Elise/Iddle_Elise.png");
	resourceManager_->addTexture("Elise_Awakening", "images/Characters/Elise/Despertar_Elise.png");
	resourceManager_->addTexture("Elise_Moving", "images/Characters/Elise/Movimiento_Elise.png");
	resourceManager_->addTexture("Elise_AttackingCrowbar", "images/Characters/Elise/AtacandoCrutch_Elise.png");
	resourceManager_->addTexture("Elise_AttackingPipe", "images/Characters/Elise/AtacandoCrowbar_Elise.png");
	resourceManager_->addTexture("Elise_AttackingAxe", "images/Characters/Elise/AtacandoAxe_Elise.png");
	resourceManager_->addTexture("Elise_AttackingCrutch", "images/Characters/Elise/AtacandoPipe_Elise.png");
	resourceManager_->addTexture("Elise_Diying", "images/Characters/Elise/Muerte_Elise.png");


	resourceManager_->addTexture("Enemigo1_Iddle", "images/Characters/Enemigo1/Enemigo1_Iddle.png");
	resourceManager_->addTexture("Enemigo1_Moving", "images/Characters/Enemigo1/Enemigo1_Moving.png");
	resourceManager_->addTexture("Enemigo1_Attacking", "images/Characters/Enemigo1/Enemigo1_Attacking.png");
	resourceManager_->addTexture("Enemigo1_Diying", "images/Characters/Enemigo1/Enemigo1_Diying.png");
	
	resourceManager_->addTexture("Enemigo2_Iddle", "images/Characters/Enemigo2/Enemigo2_Iddle.png");
	resourceManager_->addTexture("Enemigo2_Moving", "images/Characters/Enemigo2/Enemigo2_Moving.png");
	resourceManager_->addTexture("Enemigo2_Attacking", "images/Characters/Enemigo2/Enemigo2_Attacking.png");
	resourceManager_->addTexture("Enemigo2_Diying", "images/Characters/Enemigo2/Enemigo2_Diying.png");
	resourceManager_->addTexture("Enemigo2_Resurrecting", "images/Characters/Enemigo2/Enemigo2_Resurrecting.png");

	resourceManager_->addTexture("Enemigo3_Iddle", "images/Characters/Enemigo3/Enemigo3_Iddle.png");
	resourceManager_->addTexture("Enemigo3_Moving", "images/Characters/Enemigo3/Enemigo3_Moving.png");
	resourceManager_->addTexture("Enemigo3_Attacking", "images/Characters/Enemigo3/Enemigo3_Attacking.png");
	resourceManager_->addTexture("Enemigo3_Diying", "images/Characters/Enemigo3/Enemigo3_Diying.png");

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
	resourceManager_->addTexture("Bandages", "images/Items/bandages.png");
	resourceManager_->addTexture("Card", "images/Items/keycard.png");
	resourceManager_->addTexture("Circuit", "images/Items/circuit.png");
	resourceManager_->addTexture("Television", "images/Items/television.png");
	resourceManager_->addTexture("Register1", "images/Items/register1.png");
	resourceManager_->addTexture("BookShelving", "images/Items/bookShelving.png");
	resourceManager_->addTexture("PiecePuzzle", "images/Items/chip.png");

	//Inventory
	resourceManager_->addTexture("Inventory", "images/Inventario/FullscreenVersions/Inventario_Full.png");
	resourceManager_->addTexture("Chest", "images/Inventario/FullscreenVersions/Cofre_Full.png");
	resourceManager_->addTexture("Craft", "images/Inventario/FullscreenVersions/Crafting_Full.png");
	resourceManager_->addTexture("Electro3", "images/Inventario/electro3.png");
	resourceManager_->addTexture("Electro3rojo", "images/Inventario/electro3rojo.png");
	resourceManager_->addTexture("Electro3naranja", "images/Inventario/electro3naranja.png");

	//Puzzle
	resourceManager_->addTexture("SlidingPuzzle", "images/puzzle.jpg");
	resourceManager_->addTexture("vara0", "images/vara.png");
	resourceManager_->addTexture("vara1", "images/vara2.png");
	resourceManager_->addTexture("vara2", "images/vara3.png");
	resourceManager_->addTexture("vara3", "images/vara4.png");
	resourceManager_->addTexture("vara4", "images/vara5.png");

	//Backgrounds
	resourceManager_->addTexture("FondoMenu", "images/Menu/FondoMenu.png");
	resourceManager_->addTexture("BgRegistro", "images/bgRegistro.png");
	resourceManager_->addTexture("BgRegistroWithPic", "images/bgRegistroWithPic.png");
	resourceManager_->addTexture("BgBook", "images/bgBook.png");
	resourceManager_->addTexture("SRMapa1", "images/SRMap/SRMap1.png");
	resourceManager_->addTexture("SRMapa2", "images/SRMap/SRMap2.png");
	resourceManager_->addTexture("SRMapa3", "images/SRMap/SRMap3.png");
	resourceManager_->addTexture("SRMapa10", "images/SRMap/SRMap10.png");
	resourceManager_->addTexture("SRMapa11", "images/SRMap/SRMap11.png");
	resourceManager_->addTexture("SliddingBG", "images/Backgrounds/SliddingBG.png");
	resourceManager_->addTexture("OrderBG", "images/Backgrounds/OrderBG.png");

	//Buttons
	resourceManager_->addTexture("BotonNuevaPartida", "images/Menu/NuevaPartida.png");
	resourceManager_->addTexture("BotonExit", "images/Menu/Exit.png");
	resourceManager_->addTexture("Button1", "images/Menu/button1.png");
	resourceManager_->addTexture("NewGameButton", "images/Menu/NewGame.png");
	resourceManager_->addTexture("LoadGameButton", "images/Menu/LoadGame.png");
	resourceManager_->addTexture("CreditsButton", "images/Menu/Credits.png");
	resourceManager_->addTexture("ExitButton", "images/Menu/Exit.png");
	resourceManager_->addTexture("BackToGameButton", "images/Menu/BackToGame.png");
	resourceManager_->addTexture("BackToMenuButton", "images/Menu/BackToMenu.png");
	resourceManager_->addTexture("ExitPause", "images/Menu/ExitPause.png");
	resourceManager_->addTexture("MenuBackground", "images/Menu/MenuBackground.png");
	resourceManager_->addTexture("PauseBackground", "images/Menu/PauseBackground.png");
	resourceManager_->addTexture("CreditsBackground", "images/Menu/CreditsBackground.png");

	//Cursors
	resourceManager_->addTexture("Cursor", "images/Cursor.png");
	resourceManager_->addTexture("InventoryCursor", "images/Inventario/CursorInventario.png");

	//Lighting
	resourceManager_->addTexture("PlayerLight", "images/Shadows/PlayerLight.png");
	resourceManager_->addTexture("Black", "images/Shadows/Black.png");
	resourceManager_->addTexture("PointLight", "images/Shadows/PointLight.png");
	resourceManager_->addTexture("Lampara1", "images/Shadows/Lampara1.png");
	resourceManager_->addTexture("TelevisionLight", "images/Shadows/Television.png");
	resourceManager_->addTexture("Emergencia", "images/Shadows/emergencia.png");
	resourceManager_->addTexture("BGtest", "images/Shadows/BGtest.png");

	resourceManager_->addTexture("Blood", "images/Shadows/blood.png");

	//AnimationTilesheet
	resourceManager_->addTexture("SecurityCameras", "images/AnimTilesheet/TileshetCameras.png");

	//Numpad
	resourceManager_->addTexture("Keypad", "images/Keypad/Keypad.png");
	resourceManager_->addTexture("Keys", "images/Keypad/ButtonsUP.png");
	resourceManager_->addTexture("Keys_", "images/Keypad/ButtonsDOWN.png");
	resourceManager_->addTexture("Numbers", "images/Keypad/numbers.png");
	resourceManager_->addTexture("Background", "images/Keypad/background.png");

	//Puertas
	resourceManager_->addTexture("PuertaAbajo", "images/AnimPuertas/PuertaAbajo.png");
	resourceManager_->addTexture("PuertaArriba", "images/AnimPuertas/PuertaArriba.png");
	resourceManager_->addTexture("PuertaDerecha", "images/AnimPuertas/PuertaDerecha.png");
	resourceManager_->addTexture("PuertaIzquierda", "images/AnimPuertas/PuertaIzquierda.png");
	resourceManager_->addTexture("PuertaAbajoEstrecha", "images/AnimPuertas/PuertaAbajoEstrecha.png");
	resourceManager_->addTexture("PuertaArribaEstrecha", "images/AnimPuertas/PuertaArribaEstrecha.png");
	resourceManager_->addTexture("PuertaDerechaEstrecha", "images/AnimPuertas/PuertaDerechaEstrecha.png");
	resourceManager_->addTexture("PuertaIzquierdaEstrecha", "images/AnimPuertas/PuertaIzquierdaEstrecha.png");
	resourceManager_->addTexture("PuertaEmergencia", "images/AnimPuertas/PuertaEmergencia.png");
	
	//CarnePuaj
	resourceManager_->addTexture("CarnePuaj", "images/CarnePuaj/carnePuaj.png");
	resourceManager_->addTexture("CarnePuajDestroyed", "images/CarnePuaj/carnePuajDestruyendose.png");

	//Elise Inventario
	resourceManager_->addTexture("EliseInventory", "images/Inventario/Elise/1.png");
	resourceManager_->addTexture("EliseInventory_Ok", "images/Inventario/Elise/2.png");
	resourceManager_->addTexture("EliseInventory_NotOk", "images/Inventario/Elise/3.png");

}

void Game::addResourcesMusic()
{
	resourceManager_->addMusic("Menu", "music/Menu.mp3");
	resourceManager_->addMusic("SafeRoom", "music/SafeRoom.mp3");
	resourceManager_->addMusic("SilenceSound", "music/AloneEffect.mp3");
}

void Game::addResourcesSoundEffects()
{
	resourceManager_->addSound("InventorySound", "sounds/OpencraftAndInventory.mp3");
	resourceManager_->addSound("SlotSound", "sounds/cambiarSlot.mp3");
	resourceManager_->addSound("ChestSound", "sounds/ChestOpen.mp3");
	resourceManager_->addSound("UnlockSound", "sounds/DesbloqueaPuerta.mp3");
	resourceManager_->addSound("LockSound", "sounds/DoorLocked.mp3");
	resourceManager_->addSound("SaveSound", "sounds/GuardarPartida.mp3");
	resourceManager_->addSound("MapSound", "sounds/mapa.mp3");
	resourceManager_->addSound("Monster3Sound", "sounds/Monstruo3Sonido.mp3");
	resourceManager_->addSound("StepSound", "sounds/pasos.mp3");
	resourceManager_->addSound("PickSound", "sounds/pickUpItepANDcraft.mp3");
	resourceManager_->addSound("CraftSound", "sounds/pickUpItepANDcraft.mp3");
	resourceManager_->addSound("BeepSound", "sounds/Pitido.wav");
	resourceManager_->addSound("DoorSound", "sounds/puerta.mp3");
	resourceManager_->addSound("RepareSound", "sounds/repare.mp3");
	resourceManager_->addSound("CrySound", "sounds/Cry.mp3");
	resourceManager_->addSound("LaughSound", "sounds/Laugh.mp3");
	resourceManager_->addSound("ScaryStepsSound", "sounds/ScarySteps.mp3");
	resourceManager_->addSound("ErrorCodeSound", "sounds/ErrorCode.wav");
	//MONSTER1
	resourceManager_->addSound("Monster1HitSound", "sounds/Monster1Hit.wav");
	resourceManager_->addSound("Monster1DeadSound", "sounds/Monster1Dead.mp3");
	resourceManager_->addSound("Monster1StepSound", "sounds/Monster1Step.mp3");
	//MONSTER2
	resourceManager_->addSound("Monster2DeadSound", "sounds/Monster2Dead.wav");
	resourceManager_->addSound("Monster2HitSound", "sounds/Monster2Hit.wav");
	resourceManager_->addSound("Monster2StepSound", "sounds/Monster2Step.mp3");
	//MONSTER3
	resourceManager_->addSound("Monster3DeadSound", "sounds/Monstruo3muerte.mp3");
	resourceManager_->addSound("Monster3StepSound", "sounds/Monstruo3Sonido.mp3");
	
	resourceManager_->addSound("MonsterRoarSound", "sounds/MonsterRoar.wav");
	resourceManager_->addSound("MonsterRoar2Sound", "sounds/MonsterRoar2.wav");
	resourceManager_->addSound("MonsterEcoSound", "sounds/MonsterEco.wav");
	resourceManager_->addSound("SuccessSound", "sounds/PuzzlesSuccess.wav");
	resourceManager_->addSound("SlideSound", "sounds/Slide.wav");
	resourceManager_->addSound("Slide2Sound", "sounds/Slide2.mp3");
	resourceManager_->addSound("CodeSuccessSound", "sounds/SuccessCode.wav");
	resourceManager_->addSound("SwitchTubeSound", "sounds/SwitchTube.wav");
	resourceManager_->addSound("BreakSound", "sounds/BreakWeapon.mp3");
	resourceManager_->addSound("DieSound", "sounds/Die.mp3");

	////Tema de elise
	resourceManager_->addSound("EliseThemeSound", "music/TemadeElise.mp3");

}

void Game::addResourcesFonts()
{
	resourceManager_->addFont("ARIAL", "fonts/ARIAL.ttf", 24);
	resourceManager_->addFont("NES-Chimera", "fonts/NES-Chimera.ttf", 24);
	resourceManager_->addFont("VCR_OSD_MONO", "fonts/VCR_OSD_MONO.ttf", 21);
	resourceManager_->addFont("VCR_OSD_MONO_32", "fonts/VCR_OSD_MONO.ttf", 32);
	resourceManager_->addFont("VCR_OSD_MONO_40", "fonts/VCR_OSD_MONO.ttf", 40);
}

void Game::registerTypeItem() {
	gameObjectFactory->registerType("Crowbar", new ItemCreator(ItemType::CROWBAR));
	gameObjectFactory->registerType("Key", new ItemCreator(ItemType::KEY));
	gameObjectFactory->registerType("Axe", new ItemCreator(ItemType::AXE));
	gameObjectFactory->registerType("Firstaid", new ItemCreator(ItemType::FIRSTAID));
	gameObjectFactory->registerType("Card", new ItemCreator(ItemType::CARD));
	gameObjectFactory->registerType("Acid", new ItemCreator(ItemType::ACID));
	gameObjectFactory->registerType("AcidChemical", new ItemCreator(ItemType::ACIDCHEMICAL));
	gameObjectFactory->registerType("Stick", new ItemCreator(ItemType::STICK));
	gameObjectFactory->registerType("Pipe", new ItemCreator(ItemType::PIPE));
	gameObjectFactory->registerType("Alcohol", new ItemCreator(ItemType::ALCOHOL));
	gameObjectFactory->registerType("Bandages", new ItemCreator(ItemType::BANDAGES));
	gameObjectFactory->registerType("GenericChemical", new ItemCreator(ItemType::GENERICCHEMICAL));
	gameObjectFactory->registerType("Biocide", new ItemCreator(ItemType::BIOCIDE));
	gameObjectFactory->registerType("PiecePuzzle", new ItemCreator(ItemType::PIECEPUZZLE));
	gameObjectFactory->registerType("Insulationtape", new ItemCreator(ItemType::INSULATIONTEPE));
	gameObjectFactory->registerType("Circuit", new ItemCreator(ItemType::CIRCUIT));
	//gameObjectFactory->registerType("Photo", new ItemCreator(ItemType::PHOTO));
	//gameObjectFactory->registerType("Masck", new ItemCreator(ItemType::MASCK));
}