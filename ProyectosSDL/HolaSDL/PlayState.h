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
#include "checkML.h"


class LightManager;

class PlayState: public GameState {

private:
	PlayState();
	static PlayState* s_pInstance;

	SDL_Renderer* renderer = nullptr;
	Level* pLevel = nullptr;

	Entity* player = nullptr;

	int mapWidth;
	int mapHeight;

	Entity* messageRenderer = nullptr;
	Entity* zoneMessageRenderer = nullptr;

	bool saveGame = false;
	bool loadGame = false;

	bool finishGame_ = false;

public:
	Entity* inventory;
	Entity* chest;
	Entity* craft;

	//COSAS DE AUDIO
	bool ambientSound = false;
	Uint32 SoundTimer;
	Uint32 ActualTimer;
	int lastSound = 9;

	Entity* fadeManager_ = nullptr;

	static PlayState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new PlayState();
		return s_pInstance;
	}
	~PlayState();
	virtual void startState();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
	virtual void saveToFile();
	virtual void loadToFile();
	virtual void resetSingleton() { s_pInstance = nullptr; };


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

	bool getFinishGame() { return finishGame_; };
	void setFinishGame(bool b) { finishGame_ = b; };
};

typedef PlayState PlayState;
