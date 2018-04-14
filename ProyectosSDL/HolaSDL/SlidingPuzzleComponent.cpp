#include "SlidingPuzzleComponent.h"



SlidingPuzzleComponent::SlidingPuzzleComponent()
{
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			if (i == 2 && j == 2) { tablero[i][j].libre = true; }
			else { tablero[i][j].libre = false; }
		}
	}

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			fichas[i][j].currentPosX = i;
			fichas[i][j].correctPosX = i;
			fichas[i][j].currentPosY = j;
			fichas[i][j].correctPosY = j;
			if (i == 2 && j == 2) { fichas[i][j].ghost = true; }
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
	SDL_Rect srcRect;
	SDL_Rect DestRect;

	SDL_Rect srcRect2 = {100, 100 , 100, 100};

	srcRect.w = resource->getTexture("SlidingPuzzle")->getWidth() / 3; //una novena parte del puzzle
	srcRect.h = resource->getTexture("SlidingPuzzle")->getHeight() / 3; //una novena parte del puzzle
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
		{
			srcRect.x = srcRect.w * (i);
			srcRect.y = srcRect.h * (j);

			DestRect = { PosCasillas[i][j].x, PosCasillas[i][j].y, AnchoPieza, AnchoPieza };

			if (!tablero[i][j].libre)
				resource->getTexture("SlidingPuzzle")->render(pRenderer, DestRect, &srcRect);
		}
	}
}

bool SlidingPuzzleComponent::combruebaVictoria()
{
	int i = 0, j = 0;
	
	bool victoria = true;
	while (i < 3 && victoria){
		while (j < 3 && victoria) {
			if (fichas[i][j].currentPosX != fichas[i][j].correctPosX
				&& fichas[i][j].currentPosY != fichas[i][j].correctPosY)
			{ victoria = false; }
			j++;
		}
		i++;
	}
	return victoria;
}

void SlidingPuzzleComponent::mueveFicha(int ficha)
{
	
}
