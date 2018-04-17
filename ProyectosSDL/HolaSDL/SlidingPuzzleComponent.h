#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"


class SlidingPuzzleComponent : public Component
{

	struct coord {
		int x;
		int y;
	};

	struct Casilla {
		bool libre;
	};

	struct ficha
	{
		int correctPosX;
		int correctPosY;
		bool ghost;
		SDL_Rect srcRect;
	};

	static const int puzzleTam = 9;
	static const int AnchoPieza = 200;
	SDL_Renderer* pRenderer = nullptr;
	ResourceManager* resource = nullptr;

public:
	SlidingPuzzleComponent();
	~SlidingPuzzleComponent();

	Casilla tablero[3][3];
	ficha fichas[3][3];

	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	virtual void render(Entity* e, Uint32 time);

private:
	bool combruebaVictoria();
	void compruebaAdyacencia(int i, int j);
	void desordena();

	coord PosCasillas[3][3]{ {{300,50}, {300,250}, {300,450}}, {{500,50},{500,250},{500,450}}, { { 700,50 },{ 700,250 },{ 700,450 } } };
};

