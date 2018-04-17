#include "SlidingPuzzle.h"

unique_ptr<SlidingPuzzle> SlidingPuzzle::s_pInstance = nullptr;

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
}

void SlidingPuzzle::handleInput(Uint32 time, SDL_Event & event)
{
	GameState::handleInput(time, event);
}

SlidingPuzzle::~SlidingPuzzle()
{
}

