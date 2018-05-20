#include "PauseState.h"
#include "Game.h"
#include "Button.h"

PauseState::PauseState() : GameState()
{

}

PauseState::~PauseState() {
}

static void resume_game(Game* game) {
	cout << "Volver al juego" << endl;
	Game::Instance()->getStateMachine()->popStateSafe();
}

static void back_to_menu(Game* game) {
	cout << "Volver al menu" << endl;
	MenuState::Instance()->setLoadingScreen(false);
	Game::Instance()->getStateMachine()->popStateSafe();
	Game::Instance()->getStateMachine()->popStateSafe();
}

static void close_game(Game* game) {
	cout << "Cerrar juego" << endl;
	Game::Instance()->stop();
}

void PauseState::startState()
{

	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());


	//Background
	Entity* bg = new Entity();
	bg->setHeight(Game::Instance()->getWindowHeight());
	bg->setWidth(Game::Instance()->getWindowWidth());
	bg->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("PauseBackground")));
	stage_.push_back(bg);

	//Add Buttons

	//Volver al juego
	Entity* newGameButton = new Entity();
	newGameButton->addComponent(new Button(resume_game, Game::Instance()->getResourceManager()->getTexture("BackToGameButton"), Vector2D((Game::Instance()->getWindowWidth()/2) - (Game::Instance()->getResourceManager()->getTexture("BackToGameButton")->getWidth()/2), 380)));
	stage_.push_back(newGameButton);

	//Volver al menu
	Entity* backToMenu = new Entity();
	backToMenu->addComponent(new Button(back_to_menu, Game::Instance()->getResourceManager()->getTexture("BackToMenuButton"), Vector2D((Game::Instance()->getWindowWidth() / 2) - (Game::Instance()->getResourceManager()->getTexture("BackToMenuButton")->getWidth() / 2), 460)));
	stage_.push_back(backToMenu);

	//Cerrar el juego
	Entity* closeGame = new Entity();
	closeGame->addComponent(new Button(close_game, Game::Instance()->getResourceManager()->getTexture("ExitPause"), Vector2D((Game::Instance()->getWindowWidth() / 2) - (Game::Instance()->getResourceManager()->getTexture("ExitPause")->getWidth() / 2), 540)));
	stage_.push_back(closeGame);

}

void PauseState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void PauseState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) { //Pressing Escape will enter pause state
			cout << "Volver al juego" << endl;
			Game::Instance()->getStateMachine()->popStateSafe();
		}
	}
}