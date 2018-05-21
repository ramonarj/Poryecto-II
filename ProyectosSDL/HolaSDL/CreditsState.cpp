#include "CreditsState.h"
#include "Game.h"
#include "Credits.h"

CreditsState::CreditsState(int statesToPop): GameState(), popStates(statesToPop) {
}

CreditsState::~CreditsState(){
}

void CreditsState::startState()
{
	targetTime = SDL_GetTicks() + 90000;

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
	string creditsImageId = "CreditsImage";
	Entity* cr = new Entity();
	//cr->setWidth(Game::Instance()->getWindowWidth());
	//cr->setHeight((Game::Instance()->getWindowWidth() / Game::Instance()->getResourceManager()->getTexture(creditsImageId)->getWidth()) * Game::Instance()->getResourceManager()->getTexture(creditsImageId)->getHeight());
	cr->setHeight(5000);
	cr->setWidth(1280);
	cr->setPosition(Vector2D(0, 650)); //Posicion inicial
	cr->addComponent(new Credits(Game::Instance(), Game::Instance()->getResourceManager()->getTexture(creditsImageId), -0.6));
	stage_.push_back(cr);

}

void CreditsState::update(Uint32 time)
{
	GameState::update(time);
	if (targetTime < time)
	{
		Game::Instance()->getStateMachine()->popStateSafe();
		if (PlayState::Instance()->getFinishGame())
		{
			MenuState::Instance()->setLoadingScreen(false);
			Game::Instance()->getStateMachine()->popStateSafe();
		}
	}
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
			for (int i = 0; i < popStates; i++) {
				Game::Instance()->getStateMachine()->popStateSafe();
			}

			//if (PlayState::Instance()->getFinishGame())
			//{
			//	MenuState::Instance()->setLoadingScreen(false);
			//	Game::Instance()->getStateMachine()->popStateSafe();
			//}
		}
	}
}
