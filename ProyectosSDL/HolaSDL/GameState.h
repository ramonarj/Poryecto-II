#pragma once
#include "GameObject.h"
#include "Entity.h"
#include <list>
#include <memory>

using namespace std;

class Game;

class GameState {

protected:
	Entity* cursor_ = nullptr;

	list<Entity*> stage_;
	list<Entity*> stageAux_;

	list<Entity*> interactibles_;
	list<Entity*> characters_;
	list<Entity*> doors_;
	list<Entity*> removedEntities_;
	list<Entity*> removedInteractibles_;
	list<Entity*> codes_;
	list<Entity*> orderPuzzles_;

	GameState();
	static unique_ptr<GameState> s_pInstance;

	void removeStage(Entity* e);
	void removeStageAux(Entity* e);
	void removeInteractible(Entity* e);
	void removeCharacter(Entity* e);
	void removeDoor(Entity* e);

public:

	static GameState* Instance()
	{
		if (s_pInstance.get() == nullptr)
			s_pInstance.reset(new GameState());
		return s_pInstance.get();
	}

	virtual ~GameState();
	virtual void startState();
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	virtual void handleInput(Uint32 time, SDL_Event& event);
	virtual void saveToFile();
	virtual void loadToFile();
	virtual void resetSingleton() {};

	void pushEntities(Entity* e) { stage_.push_back(e); };
	list<Entity*>* getStage() { return &stage_; };
	list<Entity*>* getStageAux() { return &stageAux_; };
	void mergeStages();

	list<Entity*>* getInteractibles() { return &interactibles_; };
	list<Entity*>* getCharacters() { return &characters_; };
	list<Entity*>* getDoors() { return &doors_; };
	list<Entity*>* getCodes() { return &codes_; };
	list<Entity*>* getOrderPuzzles() { return &orderPuzzles_; };
	Entity* getCursor() { return cursor_; };
	void removeEntities();	// sacar las entidades que se quieren eliminar de cada vector y hacer delete de ellas (se llama al final de cada tick)
	void removeEntity(Entity* e);	// método que se llama cuando quieres eliminar una entidad
	void removeInteractibleOfStage(Entity* e);	//método que se llama cuando quieres eliminar un item del escenario para meterlo en el inventario
};


typedef GameState GameState;

