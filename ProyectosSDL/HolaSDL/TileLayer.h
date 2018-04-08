#pragma once
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Camera.h"

class TileLayer : public Layer
{
public:

	TileLayer(int tileSize, int mapWidth, int mapHeight, const
		std::vector<Tileset>& tilesets);
	virtual void update(Level* pLevel, Uint32 time);
	virtual void render();
	virtual void handleInput(Uint32 time, SDL_Event& event);

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; };
	void setTileSize(int tileSize) { m_tileSize = tileSize; };
	void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; };

	int getTileSize() { return m_tileSize; }

	const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; }

	Tileset getTilesetByID(int tileID);

	const Vector2D getPosition() { return m_position; }

private:

	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	int m_mapHeight;
	int m_mapWidth;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset>& m_tilesets;

	std::vector<std::vector<int>> m_tileIDs;

	int zoom;
};