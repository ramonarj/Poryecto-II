#pragma once

#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelParser.h"
#include "Level.h"

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

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 3000;
	const static int _WINDOW_HEIGHT_ = 1600;
	bool exit_;
	std::vector<Entity*> actors_;

	Level* pLevel = nullptr;

	Game();
	static Game* s_pInstance;
};
typedef Game Game;
