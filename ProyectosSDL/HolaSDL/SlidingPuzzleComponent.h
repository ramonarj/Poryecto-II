#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"


class SlidingPuzzleComponent : public Component
{

	struct coord {
		int x;
		int y;
	};

	struct Casilla {
		bool libre;
		int pos;
	};

	struct ficha
	{
		int currentPos;
		int correctPos;
		SDL_Rect fichaDest;
		bool ghost;
	};

	const int puzzleTam = 9;

public:
	SlidingPuzzleComponent();
	~SlidingPuzzleComponent();

	Casilla tablero[3][3];
	ficha fichas[3][3];

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

	bool combruebaVictoria();
	void mueveFicha(int ficha);
};

