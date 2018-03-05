#include "ResourceManager.h"
#include "Game.h"


ResourceManager::ResourceManager()
{
	textures_.insert(pair<string, Texture*> ("tennis", new Texture(Game::Instance()->getRenderer(), "images/tennis_ball.png")));
	
	Texture* test = textures_["tennis"];
}


ResourceManager::~ResourceManager()
{
}
