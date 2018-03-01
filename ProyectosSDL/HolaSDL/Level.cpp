#include "Level.h"
#include "Texture.h"
#include "Game.h"
#include "Layer.h"
#include "TileLayer.h"
#include <math.h>

Level::Level()
{
}

Level::~Level()
{
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}