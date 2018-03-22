#include "PlayState.h"
#include "Game.h"

PlayState* PlayState::s_pInstance = 0;

PlayState::PlayState(): GameState(){ //Constructora de nueva partida
	
}


PlayState::~PlayState() {
	
}

void PlayState::startState()
{
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("levels/Mapa.tmx");

	mapWidth = levelParser.mapWidth;
	mapHeight = levelParser.mapHeight;

	player = Game::Instance()->getEntityWithComponent<Player>();
	Camera::Instance()->setTarget(player);

	Enemy* enemyComp = Game::Instance()->getEntityWithComponent<Enemy>()->getComponent<Enemy>();
	enemyComp -> addPlayer(player);



	//Música
	//Game::Instance()->getResourceManager()->getMusic("SafeRoom")->play();

	//Item
	Entity* palo = new Entity(10, 20);
	palo->addComponent(new Weapon(ItemType::STICK, "Stick"));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();

	Entity* palo2 = new Entity(10, 20);
	palo2->addComponent(new Weapon(ItemType::LEVER, "Lever"));
	stage_.push_back(palo2);

	Entity* insulationTape = new Entity(15, 25);
	insulationTape->addComponent(new InsulationTape("InsulationTape"));
	stage_.push_back(insulationTape);
	insulationTape->getComponent<InsulationTape>()->use(palo);

	chest = new Entity(0, 0);
	Chest* chestComp = new Chest();
	chest->addComponent(chestComp);
	chest->setActive(false);
	stage_.push_back(chest);

	inventory = new Entity(0, 0);
	Inventory* invtComp = new Inventory();
	inventory->addComponent(invtComp);
	inventory->setActive(false);
	stage_.push_back(inventory);

	

	invtComp->addItem(insulationTape);
	invtComp->addItem(palo2);
	invtComp->addItem(palo);
}

void PlayState::update(Uint32 time)
{
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
