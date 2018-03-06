#pragma once
#include <iostream>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
#include "Entity.h"

class TileLayer;

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level
{
public:

	~Level();

	void update(Uint32 time);
	void render(Uint32 time);
	void handleInput(Uint32 time, SDL_Event& event);

	std::vector<Tileset>* getTilesets() { return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }
	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }

	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }

	Entity* getPlayer() { return pPlayer; }
	void setPlayer(Entity* player) { pPlayer = player; };

private:

	friend class LevelParser;

	Level();

	std::vector<Layer*> m_layers;
	std::vector<Tileset> m_tilesets;
	std::vector<TileLayer*> m_collisionLayers;

	Entity* pPlayer = nullptr; //Puntero a player
};