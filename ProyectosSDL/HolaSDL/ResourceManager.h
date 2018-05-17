#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "checkML.h"
#include <map>
#include <string>
#include "Texture.h"
#include "Music.h"
#include "Font.h"
#include "SoundEffect.h"

using namespace std;

class Game;

class ResourceManager
{
private:
	Game* game_;
	map <string, Texture*> textures_;
	map <string, Music*> music_;
	map <string, SoundEffect*> sounds_;
	map <string, Font*> fonts_;

	void deleteTextures();
	void deleteMusic();
	void deleteSounds();
	void deleteFonts();


public:
	ResourceManager(Game* game);
	~ResourceManager();

	//Textures
	void addTexture(string id, string filepath);
	Texture* getTexture(string id);

	//Music
	void addMusic(string id, string filepath);
	Music* getMusic(string id);

	//Sounds
	void addSound(string id, string filepath);
	SoundEffect* getSound(string id);

	//Fonts
	void addFont(string id, string filepath, int fontSize);
	Font* getFont(string id);

};

#endif /* RESOURCEMANAGER_H_ */