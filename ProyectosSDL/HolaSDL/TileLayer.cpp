#include "TileLayer.h"
#include "Texture.h"
#include "Game.h"
#include "PlayState.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight,
	const std::vector<Tileset>& tilesets) : m_tileSize(tileSize),
	m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;
}

void TileLayer::update(Level* pLevel, Uint32 time)
{
	
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;

	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;

	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	int iniRow = Camera::Instance()->getPosition().getY() / m_tileSize;
	int iniCol = Camera::Instance()->getPosition().getX() / m_tileSize;

	int finRow = (Camera::Instance()->getPosition().getY() + Game::Instance()->getWindowHeight()) / m_tileSize + 2;
	int finCol = (Camera::Instance()->getPosition().getX() + Game::Instance()->getWindowWidth()) / m_tileSize + 2;

	int test = 0;
	for (int i = iniRow; i < finRow; i++)
	{
		for (int j = iniCol; j < finCol; j++)
		{
			int id = m_tileIDs[i + y][j + x];
			if (id == 0)
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id);
			id--;

			Texture::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (((j * m_tileSize) - x2) - Camera::Instance()->getPosition().getX()), ((i * m_tileSize) - y2) - Camera::Instance()->getPosition().getY(), m_tileSize, m_tileSize,
				((id - (tileset.firstGridID - 1)) / tileset.numColumns), ((id - (tileset.firstGridID - 1)) % tileset.numColumns), Game::Instance()->getRenderer());
		}
	}
}

void TileLayer::handleInput(Uint32 time, SDL_Event & event)
{
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}
