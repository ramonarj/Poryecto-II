#pragma once

#include "Entity.h"
#include <string>
#include <map>
#include <memory>
#include "checkML.h"


class Game;

class BaseCreator
{
public:
	virtual Entity* createEntity() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
	static GameObjectFactory* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new GameObjectFactory());
		return s_pInstance.get();
	}
	~GameObjectFactory() {
		for (auto&& m : m_creators) {
			delete m.second;
		}
		m_creators.clear();
	};

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
		
		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;
		return true;
	}

	Entity* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "Could not find type: " << typeID << "\n";
			return NULL;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createEntity();
	}

private:
	GameObjectFactory() {}

	static unique_ptr<GameObjectFactory> s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;
