#include "MenuState.h"
#include "Game.h"
#include "Button.h"

unique_ptr<MenuState> MenuState::s_pInstance = nullptr;

MenuState::MenuState() : GameState() //, pRenderer(nullptr), resource(nullptr), width(0), height(0)
{ 

}


MenuState::~MenuState() {
}


static void new_game(Game* game) {
	cout << "Iniciar nueva partida" << endl;
	Game::Instance()->getStateMachine()->pushState(PlayState::Instance());
}

static void load_game(Game* game) {
	cout << "Iniciar partida cargada" << endl;
}

static void credits_button(Game* game) {
	cout << "Iniciar creditos" << endl;
	Game::Instance()->getStateMachine()->pushState(new CreditsState());
}

static void close_game(Game* game) {
	cout << "Cerrar juego" << endl;
	Game::Instance()->stop();
}


void MenuState::startState()
{
	Game::Instance()->getResourceManager()->getMusic("Menu")->play();
	
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());

	//Background
	Entity* bg = new Entity();
	bg->setHeight(Game::Instance()->getWindowHeight());
	bg->setWidth(Game::Instance()->getWindowWidth());
	bg->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("MenuBackground")));
	stage_.push_back(bg);

	//Add Buttons

	//Nueva partida
	Entity* newGameButton = new Entity();
	newGameButton->addComponent(new Button(new_game, Game::Instance()->getResourceManager()->getTexture("NewGameButton"), Vector2D(0,380)));
	stage_.push_back(newGameButton);

	//Cargar Partida
	Entity* closeButton = new Entity();
	closeButton->addComponent(new Button(load_game, Game::Instance()->getResourceManager()->getTexture("LoadGameButton"), Vector2D(0, 460)));
	stage_.push_back(closeButton);

	//Creditos
	Entity* creditsButton = new Entity();
	creditsButton->addComponent(new Button(credits_button, Game::Instance()->getResourceManager()->getTexture("CreditsButton"), Vector2D(0, 540)));
	stage_.push_back(creditsButton);

	//Salir
	Entity* ExitButton = new Entity();
	ExitButton->addComponent(new Button(close_game, Game::Instance()->getResourceManager()->getTexture("ExitButton"), Vector2D(0, 620)));
	stage_.push_back(ExitButton);

}

void MenuState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}