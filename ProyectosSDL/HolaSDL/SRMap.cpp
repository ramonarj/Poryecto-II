#include "SRMap.h"



SRMap::SRMap() : mapActive_(false), image_(nullptr)
{
}


SRMap::~SRMap()
{
	delete image_;
}

void SRMap::interact(Entity * e)
{
	AnimationRenderer* animPlayer = PlayState::Instance()->getPlayer()->getComponent<AnimationRenderer>();

	if ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1))
	{

		if (!mapActive_) {
			PlayState::Instance()->getPlayer()->setIsReading(true);
			mapActive_ = true;
		}
		else {
			PlayState::Instance()->getPlayer()->setIsReading(false);
			mapActive_ = false;
		}
	}
}

void SRMap::load(int numMap, std::string ori)
{
	ori_ = ori;
	image_ = Game::Instance()->getResourceManager()->getTexture("SRMapa" + to_string(numMap));
}

void SRMap::render(Entity * o, Uint32 time)
{
	SDL_Rect destRect RECT(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight());
	if (mapActive_)
		image_->render(Game::Instance()->getRenderer(), destRect);
}
