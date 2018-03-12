#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include "Texture.h"
#include "Music.h"

using namespace std;

class Game;

class ResourceManager
{
private:
	Game* game_;
	map <string, Texture*> textures_;
	map <string, Music*> music_;

public:
	ResourceManager(Game* game);
	~ResourceManager();
	void addTexture(string id, string filepath);
	Texture* getTexture(string id);
	void addMusic(string id, string filepath);
	Music* getMusic(string id);

};

#endif /* RESOURCEMANAGER_H_ */