#include "ResourceManager.h"
#include "Game.h"

ResourceManager::ResourceManager(Game* game) : game_(game) {
}

ResourceManager::~ResourceManager() {
}

// Textures ------------------------------------------------------------
void ResourceManager::addTexture(string id, string filepath) {
	textures_.insert(pair<string, Texture*>(id, new Texture(game_->getRenderer(), FOLDER + filepath)));
}

Texture * ResourceManager::getTexture(string id) {
	return textures_[id];
}

// Music ------------------------------------------------------------
void ResourceManager::addMusic(string id, string filepath) {
	music_.insert(pair<string, Music*>(id, new Music(FOLDER + filepath)));
}

Music * ResourceManager::getMusic(string id) {
	return music_[id];
}

// Sounds ------------------------------------------------------------
void ResourceManager::addSound(string id, string filepath) {
	sounds_.insert(pair<string,SoundEffect*>(id, new SoundEffect(FOLDER + filepath)));
}

SoundEffect * ResourceManager::getSound(string id) {
	return sounds_[id];
}

// Fonts ------------------------------------------------------------
void ResourceManager::addFont(string id, string filepath, int fontSize) {
	fonts_.insert(pair<string, Font*>(id, new Font(FOLDER + filepath, fontSize)));
}

Font * ResourceManager::getFont(string id) {
	return fonts_[id];
}