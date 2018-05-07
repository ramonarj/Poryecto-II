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
class Entity;

class LevelParser
{

public:
	Level * parseLevel(const char* stateFile);

	int mapWidth;
	int mapHeight;

private:

	void parseTilesets(TiXmlElement* pTilesetRoot,
		std::vector<Tileset>* pTilesets);

	void parseTileLayer(TiXmlElement* pTileElement,
		std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets,
		std::vector<TileLayer*> *pCollisionLayers);


	void parseTextures(TiXmlElement* pTextureRoot);

	void parseObjectLayer(TiXmlElement* pObjectElement,
		std::vector<Layer*> *pLayers, Level* pLevel);

	void loadCharacters(TiXmlElement* e, Entity* pEntity, int life, int damage, int numEnemy);
	void loadRegister(TiXmlElement * e, Entity* pEntity, int registerFile, int floorRegister);
	void loadSRMap(Entity* pEntity, int numMap, std::string orientacion);
	void loadCode(Entity* pEntity, int numDoor, int code);

	int m_tileSize;
	int m_width;
	int m_height;

	int zoom;

	int numEnemyFile = 0;
	int numItemFile = 0;
};



