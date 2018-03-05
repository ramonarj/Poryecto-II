#include "TileLayer.h"
#include "Texture.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight,
	const std::vector<Tileset>& tilesets) : m_tileSize(tileSize),
	m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;
	m_mapWidth = mapWidth;
}

void TileLayer::update(Level* pLevel, Uint32 time)
{
	m_position = m_position + m_velocity;
	//m_velocity.setX(1);
}

void TileLayer::render(Uint32 time)
{
	/*int x, y, x2, y2 = 0;
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;
	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j + x];
			if (id == 0)
			{
				continue;
			}
			Tileset tileset = getTilesetByID(id);
			id--;
			Texture::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing,
				(j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns,
				Game::Instance()->getRenderer());
		}
	}*/

	int x, y, x2, y2 = 0;
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;
	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j + x];
			if (id == 0)
			{
				continue;
			}
			// if outside the viewable area then skip the tile
			if (((j * m_tileSize) - x2) - Camera::Instance()->getPosition().getX() < -m_tileSize 
				|| ((j * m_tileSize) - x2) - Camera::Instance()->getPosition().getX() > Game::Instance()->getWindowWidth())
			{
				continue;
			}
			Tileset tileset = getTilesetByID(id);
			id--;
			// draw the tile into position while offsetting its xposition by
				// subtracting the camera position
				Texture::Instance()->drawTile(tileset.name,
					tileset.margin, tileset.spacing, ((j * m_tileSize) - x2) -
					Camera::Instance()->getPosition().getX(), ((i * m_tileSize)
						- y2), m_tileSize, m_tileSize, (id - (tileset.firstGridID -
							1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) %
					tileset.numColumns, Game::Instance()->getRenderer());
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID&&tileID < m_tilesets[i +
				1].firstGridID)
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
