#include "Level.h"
#include "Texture.h"
#include "Game.h"
#include "Layer.h"
#include "TileLayer.h"
#include <math.h>

Level::Level() {
}

Level::~Level() {
	freeMemory();
}

void Level::freeMemory()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		delete m_layers[i];
	}
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::handleInput(Uint32 time, SDL_Event & event)
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->handleInput(time, event);
	}
}

void Level::update(Uint32 time)
{
	CollisionManager::Instance()->checkEntityTileCollision((*Game::Instance()->stateMachine_.currentState()->getStage()), m_collisionLayers);
}