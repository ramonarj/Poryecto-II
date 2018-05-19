#include "KeypadScreen.h"
#include "Game.h"


KeypadScreen::KeypadScreen(SDL_Renderer* pRenderer, float h, float w) :pRenderer_(pRenderer)
{
	//cout << "I'm working" << endl;
	if (resource == nullptr) resource = Game::Instance()->getResourceManager();
	image_ = resource->getTexture("Numbers");
	src.h = image_->getHeight() / 4;
	src.w = image_->getWidth() / 3;

	dest.h = (image_->getHeight() / 4) * h;
	dest.w = (image_->getWidth() / 3) * w;
	dest.y = 80;
}

void KeypadScreen::update(Uint32 time) {
	if (timeOn + 500 < time) {
		timeOn = time;
		if (on) on = false;
		else on = true;
	}
}

void KeypadScreen::render(Uint32 time) {
	bool firstNum = false;
	pair <int, int> p;
	for (int i = 0; i < 4; i++) {
		if (sequence.size() > i)
			p = numero(sequence[i]);
		else {
			if (!firstNum && on)
				p = numero(' ');
			else
				p = numero('_');
			firstNum = true;
		}
		src.x = p.second * src.w;
		src.y = p.first * src.h;

		dest.x = 445 + 17 * i + i*dest.w;

		image_->render(pRenderer_, dest, &src);
	}
}

pair <int, int> KeypadScreen::numero(char s){
	int i = 3, j = 0;
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
	case '_':
		i = 3;
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
