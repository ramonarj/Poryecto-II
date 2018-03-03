#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game): GameState(game){ //Constructora de nueva partida
												   //Jugador
	Entity* player = new Entity(game_, 2, 2);
	player->addLogicComponent(new Player(5));
	stage_.push_back(player);

	//Enemigo
	Entity* enemy = new Entity(game_, 20, 10);
	enemy->addLogicComponent(new Enemy(player, 2));
	stage_.push_back(enemy);

	//Item
	Entity* palo = new Entity(game_, 10, 20);
	palo->addLogicComponent(new Weapon(ItemType::Stick));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();

	Entity* insulationTape = new Entity(game_, 15, 25);
	insulationTape->addLogicComponent(new InsulationTape());
	stage_.push_back(insulationTape);
	insulationTape->getComponent<InsulationTape>()->useItem(palo);
}


PlayState::~PlayState() {
	
}

void PlayState::render(Uint32 time)
{
	//SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x2222222FF)); //Color de fondo
	SDL_RenderClear(game_->getRenderer());
	game_->getLevel()->render();
	GameState::render(time);
	SDL_RenderPresent(game_->getRenderer());
}
