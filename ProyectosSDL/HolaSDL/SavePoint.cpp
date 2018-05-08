#include "SavePoint.h"



SavePoint::SavePoint()
{
}


SavePoint::~SavePoint()
{
}

void SavePoint::interact(Entity * e)
{
	PlayState::Instance()->setSaveGame(true);
	Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->setDoFade(true, 10);
}
