#pragma once
#include "Component.h"
#include "Font.h"
#include <vector>
#include "Game.h"

using namespace std;

class TextNote : public Component {
public:
	TextNote(Game* game_, string text);
	~TextNote();
	virtual void render(Entity* e, Uint32 time);

private:

	SDL_Renderer* renderer_;
	Font* font_;
	Vector2D pos_;
	SDL_Color color_;
	vector<string> textLines;
	vector<Texture> textTextures_; //MAYBE NO HACE FALTA
};

