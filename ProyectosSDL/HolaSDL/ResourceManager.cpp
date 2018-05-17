#include "ResourceManager.h"
#include "Game.h"

ResourceManager::ResourceManager(Game* game) : game_(game) {
}

ResourceManager::~ResourceManager() {
	//deleteTextures();
	//deleteMusic();
	//deleteSounds();
	//deleteFonts();
}

// Textures ------------------------------------------------------------
void ResourceManager::addTexture(string id, string filepath) {
	textures_.insert(pair<string, Texture*>(id, new Texture(game_->getRenderer(), FOLDER + filepath)));
}

Texture * ResourceManager::getTexture(string id) {
	return textures_[id];
}

void ResourceManager::deleteTextures() {
	for (auto&& t : textures_) {
		delete t.second;
	}
	textures_.clear();
}

// Music ------------------------------------------------------------
void ResourceManager::addMusic(string id, string filepath) {
	music_.insert(pair<string, Music*>(id, new Music(FOLDER + filepath)));
}

Music * ResourceManager::getMusic(string id) {
	return music_[id];
}

void ResourceManager::deleteMusic() {
	for (auto&& m : music_) {
		delete m.second;
	}
	music_.clear();
}

// Sounds ------------------------------------------------------------
void ResourceManager::addSound(string id, string filepath) {
	sounds_.insert(pair<string,SoundEffect*>(id, new SoundEffect(FOLDER + filepath)));
}

SoundEffect * ResourceManager::getSound(string id) {
	return sounds_[id];
}

void ResourceManager::deleteSounds() {
	for (auto&& s : sounds_) {
		delete s.second;
	}
	sounds_.clear();
}

// Fonts ------------------------------------------------------------
void ResourceManager::addFont(string id, string filepath, int fontSize) {
	fonts_.insert(pair<string, Font*>(id, new Font(FOLDER + filepath, fontSize)));
}

Font * ResourceManager::getFont(string id) {
	return fonts_[id];
}

void ResourceManager::deleteFonts() {
	for (auto&& f : fonts_) {
		delete f.second;
	}
	fonts_.clear();
}