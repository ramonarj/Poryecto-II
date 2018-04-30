#pragma once
#include "SDLGame.h"

#include "checkML.h"
#include <vector>
#include <memory>

#include "SDLGame.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Weapon.h"
#include "FirstAid.h"
#include "InsulationTape.h"
#include "Key.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "MenuState.h"
#include "LightTestState.h"
#include "Level.h"
#include "BaseControllerInput.h"
#include "KeyBoardInputComponent.h"
#include "ControllerInputComponent.h"
#include "ResourceManager.h"
#include "GameObjectFactory.h"
#include "AnimationRenderer.h"
#include "EnemyAnimationComponent.h"
#include "PlayerAnimationComponent.h"

//const string FOLDER = "../HolaSDL/";
const string FOLDER = "";

const string SAVE_FOLDER = "/saveGame/";

class Game : public SDLGame {

public:

	static Game* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new Game());
		return s_pInstance.get();
	}
	//Game();
	virtual ~Game();

	GameStateMachine stateMachine_;

	// from SDLGame
	void start();
	void stop();

	ResourceManager* getResourceManager() { return resourceManager_; };

	template<typename T>
	Entity* getEntityWithComponent()
	{
		for (Entity* e : *getStateMachine()->currentState()->getStage()) {
			if (e->getComponent<T>() != nullptr)
				return e;
		}

		//If Entity not found
		return nullptr;
	};

	GameStateMachine* getStateMachine() { return &stateMachine_; };
	void setFullScreen();

private:
	Game();
	static unique_ptr<Game> s_pInstance;
	ResourceManager* resourceManager_;

	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	//void update(Uint32 time);
	//void render(Uint32 time);

	void addGameObjectsFactory();
	void addResourcesTexture();
	void addResourcesMusic();
	void addResourcesSoundEffects();
	void addResourcesFonts();

	void registerTypeItem();

	const static int _WINDOW_WIDTH_ = 1280;
	const static int _WINDOW_HEIGHT_ = 720;
	bool exit_;
	std::vector<Entity*> actors_;

	GameObjectFactory* gameObjectFactory = TheGameObjectFactory::Instance();
};

typedef Game Game;