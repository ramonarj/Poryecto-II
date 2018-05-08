#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "TextNote.h"
#include "Inventory.h"
#include "Chest.h"
#include "Craft.h"
#include "Movable.h"
#include "MouseInputComponent.h"
#include "StaticImageRender.h"
#include <memory>

class LightManager;

class PlayState: public GameState {

private:
	PlayState();
	static unique_ptr<PlayState> s_pInstance;

	SDL_Renderer* renderer = nullptr;
	Level* pLevel = nullptr;

	Entity* player = nullptr;

	int mapWidth;
	int mapHeight;

	Entity* messageRenderer = nullptr;
	Entity* zoneMessageRenderer = nullptr;

	bool saveGame = false;
	bool loadGame = false;

public:
	Entity* inventory;
	Entity* chest;
	Entity* craft;

	Entity* fadeManager_ = nullptr;

	static PlayState* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new PlayState());
		return s_pInstance.get();
	}
	~PlayState();
	virtual void startState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
	virtual void saveToFile();
	virtual void loadToFile();

	//Devuelve al jugador
	Entity* getPlayer() { return player; };

	Entity* getMessageRenderer() { return messageRenderer; };
	Entity* getZoneMessageRenderer() { return zoneMessageRenderer; };
	int getMapWidth() { return mapWidth; };
	int getMapHeight() { return mapHeight; };

	bool getSaveGame() { return saveGame; };
	void setSaveGame(bool b) { saveGame = b; };

	bool getLoadGame() { return loadGame; };
	void setLoadGame(bool b) { loadGame = b; };
};

typedef PlayState PlayState;
