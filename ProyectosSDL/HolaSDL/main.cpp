#include <math.h>
#include "Game.h"
#include "checkML.h"

using namespace std;

int main(int ac, char** av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game::Instance()->start();

	return 0;
}
