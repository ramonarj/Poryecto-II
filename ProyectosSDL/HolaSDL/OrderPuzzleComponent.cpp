#include "OrderPuzzleComponent.h"




OrderPuzzleComponent::OrderPuzzleComponent()
{
	if (pRenderer == nullptr) pRenderer = Game::Instance()->getRenderer();
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();

	for (int i = 0; i < 5; i++){
		puzzle[i].correctPos = i;
		puzzle[i].currentPos = i;
		puzzle[i].text = "vara" + to_string(i);
	}

	desordena();
}


OrderPuzzleComponent::~OrderPuzzleComponent()
{
}

void OrderPuzzleComponent::switchPiece(int p1, int p2)
{
	cout << p1 << " " << p2 << "\n";

	//CON EL ULTIMO DE LOS 3 IF YA ESTARÍA BIEN FUNCIONAL PERO HACE COMPROBACIONES CON VALORES 
	//QUE ESTAN FUERA DEL RANGO DEL ARRAY ASÍ QUE POR SEGURIDAD, PARA EVITAR TENER ALGUN PROBLEMA
	//FUTURO AÑADO LOS DOS IF DE DELANTE COMO CASOS ESPECIALES EN LOS BORDES PARA NO HACER COMPROBACIONES
	//FUERA DE RANGO
	bool cambio = false;

	if (p1 == 0 && puzzle[p1 + 1].currentPos == puzzle[p2].currentPos){ cambio = true; }
	else if (p1 == 4 && puzzle[p1 - 1].currentPos == puzzle[p2].currentPos){ cambio = true; }
	else if (puzzle[p1 + 1].currentPos == puzzle[p2].currentPos || puzzle[p1 - 1].currentPos == puzzle[p2].currentPos) { cambio = true; }

	if(cambio)
	{
		piece aux = puzzle[p1];
		puzzle[p1].text = puzzle[p2].text;
		puzzle[p1].currentPos = puzzle[p2].currentPos;
		puzzle[p2].text = aux.text;
		puzzle[p2].currentPos = aux.currentPos;
	}
}

bool OrderPuzzleComponent::compruebaVictoria()
{
	bool victoria = true;
	int i = 0;
	while (i < 5 && victoria)
	{
		if (puzzle[i].currentPos != puzzle[i].correctPos) { victoria = false; }
		i++;
	}
	return victoria;
}

void OrderPuzzleComponent::desordena()
{
	bool firstTime = true;
	while(compruebaVictoria() || firstTime)
	for (int i = 0; i < 15; i++) {
		int rand1 = rand() % 5;
		if (rand1 == 0) { switchPiece(rand1, rand1 + 1); }
		else if (rand1 == 4) { switchPiece(rand1, rand1 - 1); }
		else
		{
			int rand2 = rand() % 3 + (rand1 - 1);
			switchPiece(rand1, rand2);
		}
		firstTime = false;
	}
}

void OrderPuzzleComponent::update(Entity * e, Uint32 time)
{
	if (compruebaVictoria())
	{
		cout << "poh hemo' ganao' \n";
	}
}

void OrderPuzzleComponent::handleInput(Entity * e, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT && state == clickState::normalMode) {

			int i = 0;
			bool clicked = false;
			while (i < 5 && !clicked)
			{

				if ((event.button.x >= 200 * (i + 1) && event.button.x <= 200 * (i + 1) + 100)
					&& (event.button.y >= 200 && event.button.y <= 500))
				{
					state = clickState::clickMode;
					pulsedPiece1 = i;
				}
				i++;
			}
		}
		else if (event.button.button == SDL_BUTTON_LEFT && state == clickState::clickMode) {

			int i = 0;
			bool clicked = false;
			while (i < 5 && !clicked)
			{

				if ((event.button.x >= 200 * (i + 1) && event.button.x <= 200 * (i + 1) + 100)
					&& (event.button.y >= 200 && event.button.y <= 500))
				{
					state = clickState::normalMode;
					pulsedPiece2 = i;

					switchPiece(pulsedPiece1, pulsedPiece2);
				}
				i++;
			}
		}
	}
}

void OrderPuzzleComponent::render(Entity * e, Uint32 time)
{
	SDL_Rect dest = { -600,-800, 2000,2000 };
	resource->getTexture("SRMapa1")->render(pRenderer, dest);

	SDL_Rect DestRect;

	for (int i = 0; i < 5; i++) {
		DestRect = { 200 * (i + 1), 200, 100, 300 };
		resource->getTexture(puzzle[i].text)->render(pRenderer, DestRect);
	}
}
