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

	bool winSound = false;
	bool desordenaSound = true;

	coord PosCasillas[3][3]{ {{340,60},{340,260},{340,460 }}, {{540,60 },{540,260 },{540,460 }}, { { 740,60 },{ 740,260 },{ 740,460 } } };
	coord markSlot;

	SlidingPuzzleController* pc = nullptr;
};

