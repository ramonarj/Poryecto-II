#pragma once
#include "Component.h"
#include <vector>
#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"

class SlidingPuzzleController;

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
		int currentPosX;
		int currentPosY;
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

	void moveMarkSlot(int a);
	void clickMark();

private:
	bool combruebaVictoria();
	void desordena();
	void renderMark(SDL_Rect DestRect);
	void compruebaAdyacencia(int i, int j);	

	coord PosCasillas[3][3]{ {{300,50},{300,250},{300,450}}, {{500,50},{500,250},{500,450}}, { { 700,50 },{ 700,250 },{ 700,450 } } };
	coord markSlot;

	SlidingPuzzleController* pc = nullptr;
};

