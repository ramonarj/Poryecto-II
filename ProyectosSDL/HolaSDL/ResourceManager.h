#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include "Texture.h"

using namespace std;

class Game;

class ResourceManager
{
private:
	Game* game_;
	map <string, Texture*> textures_;

public:
	ResourceManager(Game* game);
	~ResourceManager();
	void addTexture(string id, string filepath);
	Texture* getTexture(string id);
};

#endif /* RESOURCEMANAGER_H_ */