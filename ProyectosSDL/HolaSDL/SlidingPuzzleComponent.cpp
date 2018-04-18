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
			fichas[i][j].correctPosX = i;
			fichas[i][j].correctPosY = j;
	
			fichas[i][j].srcRect.w = resource->getTexture("SlidingPuzzle")->getWidth() / 3; //una novena parte del puzzle
			fichas[i][j].srcRect.h = resource->getTexture("SlidingPuzzle")->getHeight() / 3; //una novena parte del puzzle
			fichas[i][j].srcRect.x = fichas[i][j].srcRect.w * (i);
			fichas[i][j].srcRect.y = fichas[i][j].srcRect.h * (j);


			if (i == 2 && j == 2) { fichas[i][j].ghost = true; }
			else { fichas[i][j].ghost = false; }
		}
	}

	desordena();
}


SlidingPuzzleComponent::~SlidingPuzzleComponent()
{
}

void SlidingPuzzleComponent::update(Entity * e, Uint32 time)
{
	if (combruebaVictoria())
	{

	}
}

void SlidingPuzzleComponent::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			cout << event.button.x << " " << event.button.y << endl;
			bool clicked = false;
			int i = 0, j = 0;

			while (i < 3 && !clicked){
				while (j < 3 && !clicked)
				{
					if ((event.button.x >= PosCasillas[i][j].x && event.button.x <= PosCasillas[i][j].x + AnchoPieza)
						&& (event.button.y >= PosCasillas[i][j].y && event.button.y <= PosCasillas[i][j].y + AnchoPieza))
					{
						clicked = true;
					}
					if(!clicked) j++;
				}
				if (!clicked) { i++; j = 0; };
			}

			if(clicked && !fichas[i][j].ghost) compruebaAdyacencia(i, j);
		}
	}
}

void SlidingPuzzleComponent::render(Entity * e, Uint32 time)
{

		SDL_Rect dest = { -600,-800, 2000,2000 };
	resource->getTexture("Firstaid")->render(pRenderer, dest);
	SDL_Rect DestRect;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
		{
			DestRect = { PosCasillas[i][j].x, PosCasillas[i][j].y, AnchoPieza, AnchoPieza };

			if (!fichas[i][j].ghost)
				resource->getTexture("SlidingPuzzle")->render(pRenderer, DestRect, &fichas[i][j].srcRect);
		}
	}

}

bool SlidingPuzzleComponent::combruebaVictoria()
{
	int i = 0, j = 0;
	
	bool victoria = true;
	while (i < 3 && victoria){
		while (j < 3 && victoria) {
			if (i != fichas[i][j].correctPosX
				&& j != fichas[i][j].correctPosY)
			{ victoria = false; }
			j++;
		}
		i++;
	}
	return victoria;
}

//COMPROBAMOS SI HAY CASILLA LIBRE EN LOS HUECOS COLINDANTES DE CASILLA QUE LLEGA AL M�TODO
void SlidingPuzzleComponent::compruebaAdyacencia(int i, int j)
{
	
	//HAY QUE REPLANTEARLO
	ficha aux = fichas[i][j];

	if(i - 1 >= 0 && fichas[i-1][j].ghost)
	{
		fichas[i][j] = fichas[i-1][j];
		fichas[i][j].ghost = true;

		fichas[i-1][j] = aux;
		fichas[i-1][j].ghost = false;
	}
	else if (i + 1 <= 2 && fichas[i + 1][j].ghost)
	{
		fichas[i][j] = fichas[i + 1][j];
		fichas[i][j].ghost = true;

		fichas[i + 1][j] = aux;
		fichas[i + 1][j].ghost = false;
	}
	else if (j - 1 >= 0 && fichas[i][j - 1].ghost)
	{
		fichas[i][j] = fichas[i][j - 1];
		fichas[i][j].ghost = true;

		fichas[i][j - 1] = aux;
		fichas[i][j - 1].ghost = false;
	}
	else if (j + 1 <= 2 && fichas[i][j + 1].ghost)
	{
		fichas[i][j] = fichas[i][j + 1];
		fichas[i][j].ghost = true;

		fichas[i][j + 1] = aux;
		fichas[i][j + 1].ghost = false;
	}	
}

void SlidingPuzzleComponent::desordena()
{
	int clicks = 150;
	int numClicks = 0;

	while (numClicks < clicks)
	{
		int i = 0, j = 0;
		bool clicked = false;

		int Xclick = rand() % AnchoPieza * 3 + PosCasillas[0][0].x;
		int Yclick = rand() % AnchoPieza * 3 + PosCasillas[0][0].y;

		while (i < 3 && !clicked) {
			while (j < 3 && !clicked)
			{
				if (Xclick >= PosCasillas[i][j].x && Xclick <= PosCasillas[i][j].x + AnchoPieza
					&& Yclick >= PosCasillas[i][j].y && Yclick <= PosCasillas[i][j].y + AnchoPieza)
				{
					clicked = true;
				}
				if (!clicked) j++;
			}
			if (!clicked) { i++; j = 0; };
		}
		if (clicked && !fichas[i][j].ghost)
		{
			compruebaAdyacencia(i, j);
			numClicks++;
		}
	}
}
