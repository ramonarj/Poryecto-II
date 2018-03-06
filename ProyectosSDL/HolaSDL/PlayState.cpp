#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game): GameState(game){ //Constructora de nueva partida
	

	Entity* inventory = new Entity(game_, 0, 0);
	Inventory* invtComp = new Inventory();
	inventory->addComponent(invtComp);
	stage_.push_back(inventory);
												   
	//Entity* player = new Entity(game_, 100, 100);	//Jugador
	//player->setWidth(200.0);
	//player->setHeight(200.0);
	//player->setVelocity(Vector2D(1.0, 0.0));
	//player->addComponent(new Player(5));
	//player->addComponent(new AnimationRenderer(game_->getResources()->getImageTexture(Resources::PruebaAnim), 12, true));
	//stage_.push_back(player);

	////Enemigo
	//Entity* enemy = new Entity(game_, 20, 10);
	//enemy->addComponent(new Enemy(player, 3));
	//stage_.push_back(enemy);

	//Item
	Entity* palo = new Entity(game_, 10, 20);
	palo->addComponent(new Weapon(ItemType::Stick));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();

	Entity* insulationTape = new Entity(game_, 15, 25);
	insulationTape->addComponent(new InsulationTape());
	stage_.push_back(insulationTape);
	insulationTape->getComponent<InsulationTape>()->useItem(palo);

	invtComp->addItem(insulationTape);
	invtComp->addItem(palo);

}


PlayState::~PlayState() {
	
}

void PlayState::render(Uint32 time)
{
	//SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x2222222FF)); //Color de fondo
	SDL_RenderClear(game_->getRenderer());
	GameState::render(time);
	game_->getLevel()->render(time);
	SDL_RenderPresent(game_->getRenderer());

	//Entity* player = Game::Instance()->getEntityWithComponent<Player>();
	
}
