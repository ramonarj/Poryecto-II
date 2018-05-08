#include "KeypadScreen.h"
#include "Game.h"


KeypadScreen::KeypadScreen(SDL_Renderer* pRenderer) :pRenderer_(pRenderer)
{
	cout << "I'm working" << endl;
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();
	image_ = resource->getTexture("Numbers");
	src.h = image_->getHeight() / 4;
	src.w = image_->getWidth() / 3;

	dest.y = 100;
	dest.h = image_->getHeight() / 4;
	dest.w = image_->getWidth() / 3;


}
void KeypadScreen::render(Uint32 time) {
	pair <int, int> p;
	for (int i = 0; i < 4; i++) {
		if (sequence.size() >= i)
			p = numero(sequence[i]);
		else
			p = numero(' ');
		src.x = p.second * src.w;
		src.y = p.first * src.h;

		dest.x = 150 + i*dest.w;

		image_->render(pRenderer_, dest, &src);
	}
}

pair <int, int> KeypadScreen::numero(char s){
	int i = 3, j=0;
	switch (s)
	{
	case '0':
		i = 3;
		j = 1;
		break;
	case '1':
		i = j = 0;
		break;
	case '2':
		i = 0;
		j = 1;
		break;
	case '3':
		i = 0;
		j = 2;
		break;
	case '4':
		i = 1;
		j = 0;
		break;
	case '5':
		i = 1;
		j = 1;
		break;
	case '6':
		i = 1;
		j = 2;
		break;
	case '7':
		i = 2;
		j = 0;
		break;
	case '8':
		i = 2;
		j = 1;
		break;
	case '9':
		i = 2;
		j = 2;
		break;
	}
	pair<int, int> n;
	n.first = i;
	n.second = j;
	return n;
}


KeypadScreen::~KeypadScreen()
{
}
