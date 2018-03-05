#pragma once
#include "SDLGame.h"

#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Weapon.h"
#include "FirstAid.h"
#include "InsulationTape.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "Level.h"

#include "AnimationRenderer.h"
class PlayerCreator;

class Game : public SDLGame {

public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	//Game();
	virtual ~Game();

	GameStateMachine stateMachine_;

	// from SDLGame
	void start();
	void stop();

	Level* getLevel() { return pLevel; };

	template<typename T>
	Entity* getEntityWithComponent()
	{
		for (Entity* e : stateMachine_.currentState()->getStage()) {
			if (e->getComponent<T>() != nullptr)
				return e;
		}

		//If Entity not found
		return nullptr;
	};

private:
	Game();
	static Game* s_pInstance;

	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	//void update(Uint32 time);
	//void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 1080;
	const static int _WINDOW_HEIGHT_ = 720;
	bool exit_;
	std::vector<Entity*> actors_;

	Level* pLevel = nullptr;
};

typedef Game Game;