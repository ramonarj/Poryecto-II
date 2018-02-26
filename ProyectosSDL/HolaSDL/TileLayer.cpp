#include "TileLayer.h"

void TileLayer::update()
{
}

void TileLayer::render()
{
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	return m_tilesets[tileID];
}
