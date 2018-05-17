#include "SlidingPuzzle.h"

SlidingPuzzle* SlidingPuzzle::s_pInstance = nullptr;

SlidingPuzzle::SlidingPuzzle()
{
}

void SlidingPuzzle::startState()
{
	cursor_ = new Entity();
	cursor_->setHeight(50);
	cursor_->setWidth(50);
	cursor_->addComponent(new StaticImageRender(Game::Instance()->getResourceManager()->getTexture("Cursor")));
	cursor_->addComponent(new MouseInputComponent());

	Entity* slidingPuzzle = new Entity(0, 0);
	slidingPuzzle->addComponent(new SlidingPuzzleComponent());
	slidingPuzzle->addComponent(new SlidingPuzzleController());
	stage_.push_back(slidingPuzzle);
}

void SlidingPuzzle::render(Uint32 time)
{
	GameState::render(time);
	SDL_RenderPresent(Game::Instance()->getRenderer());
}

void SlidingPuzzle::update(Uint32 time)
{
	GameState::update(time);

	if(pop_)
		Game::Instance()->getStateMachine()->popState();
}

void SlidingPuzzle::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}

SlidingPuzzle::~SlidingPuzzle()
{
}

