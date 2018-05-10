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
	Entity* player = PlayState::Instance()->getPlayer();
	PlayerAnimationComponent* animPlayer = player->getComponent<PlayerAnimationComponent>();

	if ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1))
	{

		if (!mapActive_) {
			player->setIsReading(true);
			mapActive_ = true;
			Game::Instance()->getResourceManager()->getSound("MapSound")->play();
		}
		else {
			player->setIsReading(false);
			mapActive_ = false;
		}
	}
}

void SRMap::load(Entity* e, int numMap, std::string ori, int calendar)
{
	ori_ = ori;
	image_ = Game::Instance()->getResourceManager()->getTexture("SRMapa" + to_string(numMap));
	if (!calendar)
		e->addComponent(new MessageTrigger("'E' para ver el mapa", "'Square/X' para ver el mapa"));
	else
		e->addComponent(new MessageTrigger("'E' para ver el calendario", "'Square/X' para ver el calendario"));
}

void SRMap::render(Entity * o, Uint32 time)
{
	SDL_Rect destRect RECT(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight());
	if (mapActive_)
		image_->render(Game::Instance()->getRenderer(), destRect);
}
