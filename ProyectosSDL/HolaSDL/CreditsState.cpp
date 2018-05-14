#include "CreditsState.h"
#include "Game.h"
#include "Credits.h"

CreditsState::CreditsState(): GameState() {
}

CreditsState::~CreditsState(){
}

void CreditsState::startState()
{
	//Cursor
	cursor_ = new Entity();
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());

	//Background
	Entity* bg = new Entity();
	bg->setHeight(Game::Instance()->getWindowHeight());
	bg->setWidth(Game::Instance()->getWindowWidth());
	bg->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("CreditsBackground")));
	stage_.push_back(bg);

	//Credits
	Entity* cr = new Entity();
	cr->setWidth(Game::Instance()->getWindowWidth());
	cr->setHeight((Game::Instance()->getWindowWidth() / Game::Instance()->getResourceManager()->getTexture("Button1")->getWidth()) * Game::Instance()->getResourceManager()->getTexture("Button1")->getHeight());
	cr->setPosition(Vector2D(0, 600)); //Posicion inicial
	cr->addComponent(new Credits(Game::Instance(), Game::Instance()->getResourceManager()->getTexture("Button1"), -1.0));
	stage_.push_back(cr);

}

void CreditsState::render(Uint32 time)
{
	SDL_RenderClear(Game::Instance()->getRenderer());
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void CreditsState::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) { //Pressing Escape will enter pause state
			cout << "Volver al juego" << endl;
			Game::Instance()->getStateMachine()->popStateSafe();
		}
	}
}
