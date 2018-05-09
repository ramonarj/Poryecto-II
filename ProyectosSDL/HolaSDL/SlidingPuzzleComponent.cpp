#include "SlidingPuzzleComponent.h"

#include "SlidingPuzzleController.h"

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
			fichas[i][j].currentPosX = i;
			fichas[i][j].currentPosY = j;
	
			fichas[i][j].srcRect.w = resource->getTexture("SlidingPuzzle")->getWidth() / 3; //una novena parte del puzzle
			fichas[i][j].srcRect.h = resource->getTexture("SlidingPuzzle")->getHeight() / 3; //una novena parte del puzzle
			fichas[i][j].srcRect.x = fichas[i][j].srcRect.w * (i);
			fichas[i][j].srcRect.y = fichas[i][j].srcRect.h * (j);


			if (i == 2 && j == 2) { fichas[i][j].ghost = true; }
			else { fichas[i][j].ghost = false; }
		}
	}

	markSlot.x = 0;
	markSlot.y = 0;

	desordena();
}


SlidingPuzzleComponent::~SlidingPuzzleComponent()
{
}

void SlidingPuzzleComponent::update(Entity * e, Uint32 time)
{
	if (combruebaVictoria())
	{
		cout << "winner winner chicken dinner\n";
	}
}

void SlidingPuzzleComponent::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
	if (pc == nullptr)
		pc = Game::Instance()->getEntityWithComponent<SlidingPuzzleController>()->getComponent<SlidingPuzzleController>();

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			cout << event.button.x << " " << event.button.y << endl;
			bool clicked = false;
			int i = 0, j = 0;

			while (i < 3 && !clicked) {
				while (j < 3 && !clicked)
				{
					if ((event.button.x >= PosCasillas[i][j].x && event.button.x <= PosCasillas[i][j].x + AnchoPieza)
						&& (event.button.y >= PosCasillas[i][j].y && event.button.y <= PosCasillas[i][j].y + AnchoPieza))
					{
						clicked = true;
					}
					if (!clicked) j++;
				}
				if (!clicked)
					{ i++; j = 0; };
			}

			if (clicked && !fichas[i][j].ghost) 
				compruebaAdyacencia(i, j);
		}
	}
}

void SlidingPuzzleComponent::render(Entity * e, Uint32 time)
{
	if (pc == nullptr)
		pc = Game::Instance()->getEntityWithComponent<SlidingPuzzleController>()->getComponent<SlidingPuzzleController>();

	SDL_Rect dest = { -600,-800, 2000,2000 };
	resource->getTexture("SRMapa1")->render(pRenderer, dest);
	SDL_Rect DestRect;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
		{
			DestRect = { PosCasillas[i][j].x, PosCasillas[i][j].y, AnchoPieza, AnchoPieza };

			if (!fichas[i][j].ghost)
				resource->getTexture("SlidingPuzzle")->render(pRenderer, DestRect, &fichas[i][j].srcRect);
		}
	}

	DestRect.w = 210;	//210-200 = 10
	DestRect.h = 210;
	DestRect.x = PosCasillas[markSlot.x][markSlot.y].x - 5;		//10/2 = 5
	DestRect.y = PosCasillas[markSlot.x][markSlot.y].y - 5;

	if(pc->joysticksInitialised())
		renderMark(DestRect);
}

bool SlidingPuzzleComponent::combruebaVictoria()
{
	int i = 0, j = 0;
	
	bool victoria = true;
	while (i < 3 && victoria){
		j = 0;
		while (j < 3 && victoria) {
			if (fichas[i][j].currentPosX != fichas[i][j].correctPosX
				|| fichas[i][j].currentPosY != fichas[i][j].correctPosY)
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
		fichas[i][j].srcRect = fichas[i-1][j].srcRect;
		fichas[i][j].currentPosX = fichas[i - 1][j].currentPosX;
		fichas[i][j].currentPosY = fichas[i - 1][j].currentPosY;
		fichas[i][j].ghost = true;

		fichas[i-1][j].srcRect = aux.srcRect;
		fichas[i - 1][j].currentPosX = aux.currentPosX;
		fichas[i - 1][j].currentPosY = aux.currentPosY;
		fichas[i-1][j].ghost = false;
	}
	else if (i + 1 <= 2 && fichas[i + 1][j].ghost)
	{
		fichas[i][j].srcRect = fichas[i + 1][j].srcRect;
		fichas[i][j].currentPosX = fichas[i + 1][j].currentPosX;
		fichas[i][j].currentPosY = fichas[i + 1][j].currentPosY;
		fichas[i][j].ghost = true;

		fichas[i + 1][j].srcRect = aux.srcRect;
		fichas[i + 1][j].currentPosX = aux.currentPosX;
		fichas[i + 1][j].currentPosY = aux.currentPosY;
		fichas[i + 1][j].ghost = false;
	}
	else if (j - 1 >= 0 && fichas[i][j - 1].ghost)
	{
		fichas[i][j].srcRect = fichas[i][j - 1].srcRect;
		fichas[i][j].currentPosX = fichas[i][j - 1].currentPosX;
		fichas[i][j].currentPosY = fichas[i][j - 1].currentPosY;
		fichas[i][j].ghost = true;

		fichas[i][j - 1].srcRect = aux.srcRect;
		fichas[i][j - 1].currentPosX = aux.currentPosX;
		fichas[i][j - 1].currentPosY = aux.currentPosY;
		fichas[i][j - 1].ghost = false;
	}
	else if (j + 1 <= 2 && fichas[i][j + 1].ghost)
	{
		fichas[i][j].srcRect = fichas[i][j + 1].srcRect;
		fichas[i][j].currentPosX = fichas[i][j + 1].currentPosX;
		fichas[i][j].currentPosY = fichas[i][j + 1].currentPosY;
		fichas[i][j].ghost = true;

		fichas[i][j + 1].srcRect = aux.srcRect;
		fichas[i][j + 1].currentPosX = aux.currentPosX;
		fichas[i][j + 1].currentPosY = aux.currentPosY;
		fichas[i][j + 1].ghost = false;
	}	
}

void SlidingPuzzleComponent::desordena()
{
	//DESORDEN SIEMPRE IGUAL
	compruebaAdyacencia(1, 2);
	compruebaAdyacencia(1, 1);
	compruebaAdyacencia(1, 0);
	compruebaAdyacencia(0, 0);
	compruebaAdyacencia(0, 1);
	compruebaAdyacencia(0, 2);
	compruebaAdyacencia(1, 2);
	compruebaAdyacencia(2, 2);
	compruebaAdyacencia(2, 1);

	//DESORDEN ALEATORIO
/*	int clicks = 150;
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
	}*/
}

void SlidingPuzzleComponent::moveMarkSlot(int a)
{
	if (a == 1) {
		if (markSlot.y > 0) {
			markSlot.y--;
		}
	}
	else if (a == 3) {
		if (markSlot.y < 2) {
			markSlot.y++;
		}
	}
	else if (a == 2) {
		if (markSlot.x < 2) {
			markSlot.x++;
		}
	}
	else if (a == 4) {
		if (markSlot.x > 0) {
			markSlot.x--;
		}
	}
}

void SlidingPuzzleComponent::renderMark(SDL_Rect DestRect) { 
	resource->getTexture("InventoryCursor")->render(pRenderer, DestRect);
}

void SlidingPuzzleComponent::clickMark() {
	if (!fichas[markSlot.x][markSlot.y].ghost)
		compruebaAdyacencia(markSlot.x, markSlot.y);
}