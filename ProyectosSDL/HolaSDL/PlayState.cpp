#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game): GameState(game){ //Constructora de nueva partida
	

	Entity* inventory = new Entity(game_, 0, 0);
	Inventory* invtComp = new Inventory();
	inventory->addComponent(invtComp);
	stage_.push_back(inventory);
			


	//Player
	Entity* player = new Entity(game_, 100, 100);	//Jugador
	player->setWidth(200.0);
	player->setHeight(200.0);
	player->setVelocity(Vector2D(0.0, 0.0));
	player->addComponent(new Player(5, 1));
	player->addComponent(new KeyBoardInputComponent(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
		SDL_SCANCODE_E, SDL_SCANCODE_SPACE, SDL_SCANCODE_I, SDL_SCANCODE_TAB, SDL_SCANCODE_RETURN));
	player->addComponent(new AnimationRenderer(game_->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
	stage_.push_back(player);


	//Enemigo
	Entity* enemy = new Entity(game_, 100, 100);
	enemy->setWidth(200.0);
	enemy->setHeight(200.0);
	enemy->setVelocity(Vector2D(1.0, 0.0));
	enemy->addComponent(new Enemy(player, 2, 2));
	enemy->addComponent(new AnimationRenderer(game_->getResources()->getImageTexture(Resources::PruebaAnim), 14, true));
	stage_.push_back(enemy);

	
	


	//Item
	Entity* palo = new Entity(game_, 10, 20);
	palo->addComponent(new Weapon(ItemType::Stick));
	stage_.push_back(palo);
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();
	palo->getComponent<Weapon>()->attack();

	Entity* insulationTape = new Entity(game_, 15, 25);
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
	game_->getLevel()->update(time);

	/*Entity* enemy = Game::Instance()->getEntityWithComponent<Player>();
	if (enemy != nullptr)
		cout << enemy->getComponent<Enemy>()->getDamage() << endl;
	else
		cout << "ee";*/
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

void PlayState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
	game_->getLevel()->handleInput(time, event);
}
