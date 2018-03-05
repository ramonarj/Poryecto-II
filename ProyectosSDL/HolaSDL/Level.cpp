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

void Level::render(Uint32 time)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render(time);
	}
}

void Level::update(Uint32 time)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update(this, time);
	}
}