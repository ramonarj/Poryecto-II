#include "MenuState.h"
#include "Game.h"
#include "Button.h"

MenuState* MenuState::s_pInstance = nullptr;

MenuState::MenuState() : GameState(), loading(false) //, pRenderer(nullptr), resource(nullptr), width(0), height(0)
{ 

}

MenuState::~MenuState() {

}


static void new_game(Game* game) {
	cout << "Iniciar nueva partida" << endl;
	Game::Instance()->getStateMachine()->pushState(PlayState::Instance());
	MenuState::Instance()->setLoadingScreen(true);
}

static void load_game(Game* game) {
	PlayState* pl = PlayState::Instance();
	pl->setLoadGame(true);
	Game::Instance()->getStateMachine()->pushState(pl);
	MenuState::Instance()->setLoadingScreen(true);

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

void MenuState::setLoadingScreen(bool b) {
	if (b) {
		SDL_Rect rect RECT(
			0,
			0,
			Game::Instance()->getWindowWidth(),
			Game::Instance()->getWindowHeight());

		SDL_RenderClear(Game::Instance()->getRenderer());
		loadingTex_->render(Game::Instance()->getRenderer(), rect);
		SDL_RenderPresent(Game::Instance()->getRenderer());
	}
	loading = b;
}

void MenuState::startState()
{
	Game::Instance()->getResourceManager()->getMusic("Menu")->play();

	loadingTex_ = Game::Instance()->getResourceManager()->getTexture("LoadingScreen");

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

void MenuState::update(Uint32 time) {
	GameState::update(time);
}

void MenuState::render(Uint32 time)
{
	if (!loading) {
		SDL_RenderClear(Game::Instance()->getRenderer());
		GameState::render(time);
		SDL_RenderPresent(Game::Instance()->getRenderer());
	}
}

void MenuState::setMenuMusic(bool b)
{
	if (b) Game::Instance()->getResourceManager()->getMusic("Menu")->play();
	else Game::Instance()->getResourceManager()->getMusic("Menu")->close();
}


