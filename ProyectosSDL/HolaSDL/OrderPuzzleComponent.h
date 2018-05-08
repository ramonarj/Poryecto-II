#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"

class OrderPuzzleComponent : public Component
{
private:

	enum clickState {normalMode, clickMode};

	struct coord {
		int x;
		int y;
	};

	struct piece {
		int currentPos;
		int correctPos;
		string text;
	};

	piece puzzle[5];
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

	clickState state = clickState::normalMode;

	int pulsedPiece1, pulsedPiece2;

	void switchPiece(int p1, int p2);
	bool compruebaVictoria();
	void desordena();

public:
	OrderPuzzleComponent();
	~OrderPuzzleComponent();

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);
};

