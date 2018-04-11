#include "SlidingPuzzleComponent.h"



SlidingPuzzleComponent::SlidingPuzzleComponent()
{
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			tablero[i][j].pos = i;
			if (i == 8) { tablero[i][j].libre = false; }
			else { tablero[i][j].libre = true; }
		}
	}

	for (int i = 0; i < puzzleTam; i++){
		for (int j = 0; j < 3; j++) {
			fichas[i][j].currentPos = i;
			fichas[i][j].correctPos = i;
			if (i == 8) { fichas[i][j].ghost = true; }
			else { fichas[i][j].ghost = false; }
		}
	}
}


SlidingPuzzleComponent::~SlidingPuzzleComponent()
{
}

void SlidingPuzzleComponent::update(Entity * e, Uint32 time)
{
}

void SlidingPuzzleComponent::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
}

void SlidingPuzzleComponent::render(Entity * e, Uint32 time)
{
}

bool SlidingPuzzleComponent::combruebaVictoria()
{
	int i = 0, j = 0;
	
	bool victoria = true;
	while (i < 3 && victoria){
		while (j < 3 && victoria) {
			if (fichas[i][j].currentPos != fichas[i][j].correctPos) { victoria = false; }
			j++;
		}
		i++;
	}
	return victoria;
}

void SlidingPuzzleComponent::mueveFicha(int ficha)
{
	
}
