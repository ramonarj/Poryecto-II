#include "PlayState.h"
#include "Game.h"
#include "PlayerLight.h"
#include "LightManager.h"
#include "Light.h"
#include "SRMap.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"
#include "FadeManager.h"
#include "BloodManager.h"

unique_ptr<PlayState> PlayState::s_pInstance = nullptr;

PlayState::PlayState() : GameState() { //Constructora de nueva partida

}


PlayState::~PlayState() {

}

void PlayState::startState()
{
	LevelParser levelParser;
	string fileMap = FOLDER + string("levels/Mapa.tmx");
	pLevel = levelParser.parseLevel(fileMap.c_str());

	mapWidth = levelParser.mapWidth;
	mapHeight = levelParser.mapHeight;

	player = Game::Instance()->getEntityWithComponent<Player>();
	Camera::Instance()->setTarget(player);

	for (Entity* e : stage_)
	{
		if (e->getComponent<Enemy>() != nullptr)
			e->getComponent<Enemy>()->addPlayer(player);
	}

	//PROBAR LOS MOVIBLES:
		//Descomentar estas dos lineas, la linea 76 del EntityCreator.h y comentar la 77 del EntityCreator.h
	//Movable* movableComp = Game::Instance()->getEntityWithComponent<Movable>()->getComponent<Movable>();
	//movableComp->addPlayer(player);

	//M�sica
	//Game::Instance()->getResourceManager()->getMusic("SafeRoom")->play();

	//CURSORº
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());
	cursor_->setActive(false);

	//Item
	/*Entity* palo = new Entity(10, 20);
	palo->addComponent(new Weapon(ItemType::STICK, "Stick"));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();

	Entity* palo2 = new Entity(10, 20);
	palo2->addComponent(new Weapon(ItemType::CROWBAR, "Crowbar"));
	stage_.push_back(palo2);

	Entity* insulationTape = new Entity(15, 25);
	insulationTape->addComponent(new InsulationTape("InsulationTape"));
	stage_.push_back(insulationTape);
	insulationTape->getComponent<InsulationTape>()->use(palo);*/

	//Iluminacion -------------------------------------------------------------
	//Entity* playerLight = new Entity(0, 0);
	//playerLight->addComponent(new PlayerLight());
	//stage_.push_back(playerLight);

	Entity* lightManagerEntity = new Entity(0, 0);
	LightManager* lightManager = new LightManager();
	lightManagerEntity->addComponent(lightManager);
	lightManagerEntity->setHeight(Game::Instance()->getWindowHeight());
	lightManagerEntity->setWidth(Game::Instance()->getWindowWidth());
	stage_.push_back(lightManagerEntity);

	lightManager->addLight(new Light(Game::Instance()->getResourceManager()->getTexture("PointLight"), 4200, 5500));
	lightManager->addLight(new Light(Game::Instance()->getResourceManager()->getTexture("PointLight"), 4800, 5500));

	//MessageRenderer----------------------------------------------------------
	messageRenderer = new Entity(0, 0);
	messageRenderer->addComponent(new MessageRenderer());
	messageRenderer->addComponent(new MessageTimer());
	stage_.push_back(messageRenderer);

	//ZoneMessageRenderer----------------------------------------------------------
	zoneMessageRenderer = new Entity(0, 0);
	zoneMessageRenderer->addComponent(new MessageRenderer());
	zoneMessageRenderer->addComponent(new MessageTimer());
	stage_.push_back(zoneMessageRenderer);

	craft = new Entity(0, 0);
	craft->addComponent(new Craft());
	craft->setActive(false);
	stage_.push_back(craft);

	chest = new Entity(0, 0);
	chest->addComponent(new Chest());
	chest->setActive(false);
	stage_.push_back(chest);

	inventory = new Entity(0, 0);
	inventory->addComponent(new Inventory());
	inventory->setActive(false);
	stage_.push_back(inventory);

	mergeStages();

	////FADE---------------------------------------------------------------------------------
	fadeManager_ = new Entity();
	fadeManager_->addComponent(new FadeManager(Game::Instance()->getResourceManager()->getTexture("Black")));
	stage_.push_back(fadeManager_);

	//Blood-------------------------------------------------------------------
	Entity* bloodManagerEntity = new Entity(0, 0);
	BloodManager* bloodManager = new BloodManager();
	bloodManagerEntity->addComponent(bloodManager);
	bloodManagerEntity->setHeight(Game::Instance()->getWindowHeight());
	bloodManagerEntity->setWidth(Game::Instance()->getWindowWidth());
	stage_.push_back(bloodManagerEntity);
}

void PlayState::update(Uint32 time)
{
	pLevel->update(time);
	GameState::update(time);
	pLevel->update(time);
}

void PlayState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	pLevel->render();
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void PlayState::handleInput(Uint32 time, SDL_Event & event)
{
	pLevel->handleInput(time, event);
	GameState::handleInput(time, event);
}

void PlayState::saveToFile()
{
	if (saveGame)
	{
		GameState::saveToFile();
		saveGame = false;
	}

}

void PlayState::loadToFile()
{
	if (loadGame)
	{
		GameState::loadToFile();
		loadGame = false;
	}
}
