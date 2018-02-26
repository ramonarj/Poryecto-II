#pragma once
#include <string>
#include <vector>
#include "Layer.h"

using namespace std;

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
	Level();
	~Level();

	void update();
	void render();

	//GETS
	vector<Tileset>* getTilesVector() { return &TileSets_V; }
	vector<Layer*>* getLayerVector() { return &Layers_V; }

protected:

	vector<Tileset> TileSets_V;
	vector<Layer*> Layers_V;

};
