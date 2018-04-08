#pragma once
#include "GameState.h"
#include "LevelParser.h"
#include "TextNote.h"
#include "Inventory.h"
#include "Chest.h"
#include "Craft.h"
#include <memory>

class PlayState: public GameState {

private:
	PlayState();
	static unique_ptr<PlayState> s_pInstance;

	SDL_Renderer* renderer;
	Level* pLevel = nullptr;

	Entity* player;

	int mapWidth;
	int mapHeight;

public:
	Entity* inventory;
	Entity* chest;
	Entity* craft;

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

	//Devuelve al jugador
	Entity* getPlayer() { return player; };
	int getMapWidth() { return mapWidth; };
	int getMapHeight() { return mapHeight; };
};

typedef PlayState PlayState;
