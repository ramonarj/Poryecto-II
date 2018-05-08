#include <string>
#include "LevelParser.h"
#include "Texture.h"
#include "Game.h"
#include "TileLayer.h"
#include "base64.h"
#include "zlib.h"
#include "Level.h"
#include "Texture.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "Door.h"
#include "SecurityCamera.h"
#include "Register.h"
#include "SRMap.h"
#include "AnimationRenderObject.h"
#include "Light.h"
#include "LightManager.h"
#include "Code.h"
#include "KeypadState.h"
#include "Countdown.h"


Level* LevelParser::parseLevel(const char *levelFile)
{
	zoom = Camera::Instance()->getZoom();

	// create a tinyXML document and load the map xml
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	// create the level object
	Level* pLevel = new Level();

	// get the root node and display some values
	TiXmlElement* pRoot = levelDocument.RootElement();

	/*std::cout << "Loading level:\n" << "Version: " << pRoot->Attribute("version") << "\n";
	std::cout << "Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
	std::cout << "Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";*/

	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);
	pRoot->Attribute("tilewidth", &m_tileSize);

	m_tileSize *= zoom;

	mapWidth = m_width * m_tileSize;
	mapHeight = m_height * m_tileSize;

	//we know that properties is the first child of the root
	TiXmlElement* pProperties = pRoot->FirstChildElement();

	// we must parse the textures needed for this level, which have been added to properties
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

	// we must now parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	// parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			parseObjectLayer(e, pLevel->getLayers(), pLevel);
			/*if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(), pLevel);
			}
			else */
			if (e->FirstChildElement()->Value() == std::string("data") ||
				(e->FirstChildElement()->NextSiblingElement() != 0 &&
					e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(),
					pLevel->getCollisionLayers());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot,
	std::vector<Tileset>* pTilesets)
{
	// first add the tileset to texture manager
	Texture::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"),
		Game::Instance()->getRenderer());
	// create a tileset object
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width",
		&tileset.width);

	pTilesetRoot->FirstChildElement()->Attribute("height",
		&tileset.height);

	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);

	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);

	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);

	tileset.spacing = 0;
	tileset.margin = 0;

	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth +
		tileset.spacing);
	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement,
	std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets,
	std::vector<TileLayer*> *pCollisionLayers)

{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width,
		m_height, *pTilesets);

	bool collidable = false;

	// tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* pDataNode = nullptr;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				if (property->Value() == std::string("property"))
				{
					if (property->Attribute("name") == std::string("collidable"))
					{
						collidable = true;
					}
				}
			}
		}

		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// uncompress zlib compression
	uLongf sizeofids = m_width * m_height * sizeof(int);
	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = ids[rows * m_width + cols];
		}
	}

	pTileLayer->setMapWidth(m_width);
	pTileLayer->setTileIDs(data);

	if (collidable)
	{
		pCollisionLayers->push_back(pTileLayer);
	}

	pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(TiXmlElement * pTextureRoot)
{
	Texture::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
		Game::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
	zoom = Camera::Instance()->getZoom();

	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();
	//std::cout << pObjectElement->FirstChildElement()->Value();

	int staticEntity;
	int collidableDoor;
	int floorRegister;

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				if (property->Value() == std::string("property"))
				{
					if (property->Attribute("name") == std::string("staticEntity"))
						property->Attribute("value", &staticEntity);

					if (property->Attribute("name") == std::string("collidableDoor"))
						property->Attribute("value", &collidableDoor);

					if (property->Attribute("name") == std::string("floorRegister"))
						property->Attribute("value", &floorRegister);
				}
			}
		}
	}

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		//std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames;
			std::string textureName = "";
			std::string orientacion;
			
			//Variables para los personajes
			int life = 0;
			int damage = 0;
			int numEnemy = 0;

			//Variables para las puertas y las llaves
			int numKey = 0;
			int numDoor = 0;
			int needKey = 0;
			string zoneName = "";
			string keyName = "";

			int numCamera = 0;

			//Variables para los registros
			int registerFile;
			int numMap;

			//Variables para el codigo de abrir puertas
			int numDoorCode = 0;
			int code = 0;

			//Variables para la cuenta atras
			int activeCountdown = 0;
			int countdown = 0;

			// get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			if (e->Attribute("type") == std::string("Puerta") || e->Attribute("type") == std::string("Camera") ||
				e->Attribute("type") == std::string("Television") || e->Attribute("type") == std::string("Register")
				|| e->Attribute("type") == std::string("SRMap") || e->Attribute("type") == std::string("SavePoint")
				|| e->Attribute("type") == std::string("Light") || e->Attribute("type") == std::string("Code")
				|| e->Attribute("type") == std::string("Countdown"))
			{
				e->Attribute("width", &width);
				e->Attribute("height", &height);
			}

			Entity* pEntity = GameObjectFactory::Instance()->create(e->Attribute("type"));

			// get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
								property->Attribute("value", &numFrames);

							else if (property->Attribute("name") == std::string("textureHeight"))
								property->Attribute("value", &height);
				
							else if (property->Attribute("name") == std::string("textureWidth"))							
								property->Attribute("value", &width);
							
							else if (property->Attribute("name") == std::string("life"))
								property->Attribute("value", &life);
							
							else if (property->Attribute("name") == std::string("damage"))
								property->Attribute("value", &damage);
						
							else if (property->Attribute("name") == std::string("numDoor"))
								property->Attribute("value", &numDoor);
							
							else if (property->Attribute("name") == std::string("dir"))
								orientacion = property->Attribute("value");
							
							else if (property->Attribute("name") == std::string("numKey"))
								property->Attribute("value", &numKey);
							
							else if (property->Attribute("name") == std::string("needKey"))
								property->Attribute("value", &needKey);
							
							else if (property->Attribute("name") == std::string("numCamera"))
								property->Attribute("value", &numCamera);
							
							else if (property->Attribute("name") == std::string("registerFile"))
								property->Attribute("value", &registerFile);
							
							else if (property->Attribute("name") == std::string("numMap"))
								property->Attribute("value", &numMap);
							
							else if (property->Attribute("name") == std::string("numEnemy"))
								property->Attribute("value", &numEnemy);

							else if (property->Attribute("name") == std::string("zoneName"))
								zoneName = property->Attribute("value");

							else if (property->Attribute("name") == std::string("textureName"))
								textureName = property->Attribute("value");

							else if (property->Attribute("name") == std::string("numDoorCode"))
								property->Attribute("value", &numDoorCode);

							else if (property->Attribute("name") == std::string("code"))
								property->Attribute("value", &code);

							else if (property->Attribute("name") == std::string("keyName"))
								keyName = property->Attribute("value");

							else if (property->Attribute("name") == std::string("activeCountdown"))
								property->Attribute("value", &activeCountdown);
							else if (property->Attribute("name") == std::string("count"))
								property->Attribute("value", &countdown);
						}
					}
				}
			}
			//Cargas de varias formas dependiendo del tipo de objeto
			pEntity->load(x * zoom, y * zoom, width * zoom, height * zoom, staticEntity, e->Attribute("name"), textureName);

			//Si es un personaje, le carga diferentes variables y lo mete en un vector
			if (e->Attribute("type") == std::string("Player") || e->Attribute("type") == std::string("Enemy"))
				loadCharacters(e, pEntity, life, damage, numEnemy);

			else if (e->Attribute("type") == std::string("Puerta"))
				pEntity->getComponent<Door>()->load(numDoor, orientacion, needKey, collidableDoor, zoneName);

			else if (e->Attribute("type") == std::string("Key"))				
				pEntity->getComponent<Key>()->load(numKey, keyName);

			else if (e->Attribute("type") == std::string("Camera"))
				pEntity->getComponent<SecurityCamera>()->load(numCamera);

			else if (e->Attribute("type") == std::string("Register"))
				loadRegister(e, pEntity, registerFile, floorRegister);

			else if (e->Attribute("type") == std::string("SRMap"))
				loadSRMap(pEntity, numMap, orientacion);

			else if (e->Attribute("type") == std::string("Code"))
				loadCode(pEntity, numDoorCode, code, orientacion);

			else if (e->Attribute("type") == std::string("Countdown"))
				pEntity->getComponent<Countdown>()->load(activeCountdown, countdown);

			if (e->Attribute("type") == std::string("Puerta"))
				Game::Instance()->stateMachine_.currentState()->getDoors()->push_back(pEntity);

			if (pEntity->getComponent<Item>() != nullptr) {
				pEntity->getComponent<Item>()->load(numItemFile);
				numItemFile++;
			}

			if (e->Attribute("type") != std::string("Register") && e->Attribute("type") != std::string("SRMap"))
				Game::Instance()->stateMachine_.currentState()->getStage()->push_back(pEntity);
		}
	}
	pLayers->push_back(pObjectLayer);
}

void LevelParser::loadCharacters(TiXmlElement* e, Entity* pEntity, int life, int damage, int numEnemy)
{
	pEntity->getComponent<Character>()->load(life, damage);
	if (e->Attribute("type") == std::string("Enemy")) {
		pEntity->getComponent<Enemy>()->load(numEnemy, numEnemyFile);
		if (numEnemy == 1)
			pEntity->addComponent(new EnemyAnimationComponent(numEnemy, Game::Instance()->getResourceManager()->getTexture("Enemigo1_Moving"), Game::Instance()->getResourceManager()->getTexture("Enemigo1_Iddle"), Game::Instance()->getResourceManager()->getTexture("Enemigo1_Attacking"), Game::Instance()->getResourceManager()->getTexture("Enemigo1_Diying"),nullptr, 150, 2, 8, 7, 6, 0));
		else if (numEnemy == 2)
			pEntity->addComponent(new EnemyAnimationComponent(numEnemy, Game::Instance()->getResourceManager()->getTexture("Enemigo2_Moving"), Game::Instance()->getResourceManager()->getTexture("Enemigo2_Iddle"), Game::Instance()->getResourceManager()->getTexture("Enemigo2_Attacking"), Game::Instance()->getResourceManager()->getTexture("Enemigo2_Diying"), Game::Instance()->getResourceManager()->getTexture("Enemigo2_Resurrecting"), 120, 2, 8, 5, 3, 4));
		else if (numEnemy == 3){
			pEntity->addComponent(new EnemyAnimationComponent(numEnemy, Game::Instance()->getResourceManager()->getTexture("Enemigo3_Moving"), Game::Instance()->getResourceManager()->getTexture("Enemigo3_Iddle"), Game::Instance()->getResourceManager()->getTexture("Enemigo3_Attacking"), Game::Instance()->getResourceManager()->getTexture("Enemigo3_Diying"), nullptr, 120, 2, 7, 7, 4, 0));
		}
		numEnemyFile++;
	}
	Game::Instance()->stateMachine_.currentState()->getCharacters()->push_back(pEntity);
}

void LevelParser::loadRegister(TiXmlElement * e, Entity* pEntity, int registerFile, int floorRegister)
{
	pEntity->getComponent<Register>()->load(registerFile);
	if (floorRegister)
	{
		if (registerFile == 1) {
			pEntity->addComponent(new AnimationRenderObject(Game::Instance()->getResourceManager()->getTexture("BookShelving"), 400, true, true, 2));
		}
		else
			pEntity->addComponent(new AnimationRenderObject(Game::Instance()->getResourceManager()->getTexture("Register1"), 400, true, true, 2));
		Game::Instance()->stateMachine_.currentState()->getStage()->push_back(pEntity);
	}
	else
	{
		Game::Instance()->stateMachine_.currentState()->getStageAux()->push_back(pEntity);
	}
}

void LevelParser::loadSRMap(Entity * pEntity, int numMap, std::string orientacion)
{
	pEntity->getComponent<SRMap>()->load(numMap, orientacion);
	Game::Instance()->stateMachine_.currentState()->getStageAux()->push_back(pEntity);
}

void LevelParser::loadCode(Entity * pEntity, int numDoor, int code, std::string dir)
{
	pEntity->getComponent<Code>()->load(numDoor, code, dir);
	KeypadState::Instance()->getCodes()->push_back(pEntity);
}
