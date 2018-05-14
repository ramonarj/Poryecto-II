#include "PlayState.h"
#include "Game.h"
#include "Light.h"
#include "SRMap.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"
#include "FadeManager.h"
#include "BloodManager.h"
#include "LightManager.h"
#include "CountdownManager.h"

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

	//Iluminacion -------------------------------------------------------------
	LightManager* lightManager = new LightManager();
	Entity* lightManagerEntity = new Entity(0, 0);
	lightManagerEntity->addComponent(lightManager);
	lightManagerEntity->setHeight(Game::Instance()->getWindowHeight());
	lightManagerEntity->setWidth(Game::Instance()->getWindowWidth());
	stage_.push_back(lightManagerEntity);

	for (Entity* e : stage_)
	{
		if (e->getName() == "Light")
		{
			string textureName = e->getTextureName();
			lightManager->addLight(new Light(Game::Instance()->getResourceManager()->getTexture(textureName), e->getPosition().getX() - Game::Instance()->getResourceManager()->getTexture(textureName)->getWidth() / 2, e->getPosition().getY() - Game::Instance()->getResourceManager()->getTexture(textureName)->getHeight() / 2));
		}
	}

	Game::Instance()->getResourceManager()->getMusic("SilenceSound")->play();

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

	//Countdown-----------------------------------------------------------------------------
	Entity* countdownManager_ = new Entity(0, 0);
	countdownManager_->addComponent(new CountdownManager());
	stage_.push_back(countdownManager_);
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
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) //Pressing Escape will enter pause state
			Game::Instance()->getStateMachine()->pushState(new PauseState());
	}
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
