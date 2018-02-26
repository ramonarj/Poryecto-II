#include "Level.h"



Level::Level()
{
}


Level::~Level()
{
}

void Level::update()
{
	for (int i = 0; i < Layers_V.size(); i++)
	{
		Layers_V[i]->update();
	}
}

void Level::render()
{
	for (int i = 0; i < Layers_V.size(); i++)
	{
		Layers_V[i]->render();
	}
}
