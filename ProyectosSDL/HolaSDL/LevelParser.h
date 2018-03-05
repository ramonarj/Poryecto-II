#pragma once
#include <iostream>
#include <vector>
#include "tinyxml.h"
#include "LoaderParams.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;
class Game;
class Texture;
class ObjectLayer;

class LevelParser
{
public:
	Level * parseLevel(const char* stateFile);

private:

	void parseTilesets(TiXmlElement* pTilesetRoot,
		std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement,
		std::vector<Layer*> *pLayers, const std::vector<Tileset>*
		pTilesets);

	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayer(TiXmlElement* pObjectElement,
		std::vector<Layer*> *pLayers);

	int m_tileSize;
	int m_width;
	int m_height;

	Level* pLevel_ = nullptr;
};

