#include "PlayState.h"
#include "Game.h"

PlayState* PlayState::s_pInstance = 0;

PlayState::PlayState(): GameState(){ //Constructora de nueva partida
	

	Entity* inventory = new Entity(0, 0);
	Inventory* invtComp = new Inventory();
	inventory->addComponent(invtComp);
	stage_.push_back(inventory);
			
	//Item
	Entity* palo = new Entity(10, 20);
	palo->addComponent(new Weapon(ItemType::Stick));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();

	Entity* insulationTape = new Entity(15, 25);
	insulationTape->addComponent(new InsulationTape());
	stage_.push_back(insulationTape);
	insulationTape->getComponent<InsulationTape>()->use(palo);


	invtComp->addItem(insulationTape);
	invtComp->addItem(insulationTape);
	invtComp->addItem(insulationTape);
	invtComp->addItem(palo);

}


PlayState::~PlayState() {
	
}

void PlayState::update(Uint32 time)
{
	GameState::update(time);
	Game::Instance()->getLevel()->update(time);

	/*Entity* enemy = Game::Instance()->getEntityWithComponent<Player>();
	if (enemy != nullptr)
		cout << enemy->getComponent<Enemy>()->getDamage() << endl;
	else
		cout << "ee";*/
}

void PlayState::render(Uint32 time)
{
	//SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x2222222FF)); //Color de fondo
	SDL_RenderClear(Game::Instance()->getRenderer());
	Game::Instance()->getLevel()->render(time);
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());


	//game_->getEntityWithComponent<Player>()->getComponent<Character>()->lif();
	//Entity* player = Game::Instance()->getEntityWithComponent<Player>();
	//cout << endl << stage_.size();
	
}

void PlayState::handleInput(Uint32 time, SDL_Event & event)
{
	Game::Instance()->getLevel()->handleInput(time, event);
	GameState::handleInput(time, event);
}
