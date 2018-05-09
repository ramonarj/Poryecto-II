#pragma once
#include "checkML.h"
#include "Component.h"
#include "Font.h"
#include <vector>
#include "Game.h"

using namespace std;

class TextNote : public Component {
public:
	TextNote(Game* game_, string txtFilePath, int x, int y, Texture* backgroundTexture);
	~TextNote();
	virtual void render(Entity* e, Uint32 time);
	void changeString(string txtFilePath);
	void setColor(SDL_Color c) { color_ = c; }
	void setFont(Font* f) { font_ = f; };
	void setAlpha(Uint8 alpha) { alpha_ = alpha; };

private:
	Texture* background_;
	int spacing_;
	SDL_Renderer* renderer_;
	Font* font_;
	Vector2D pos_;
	SDL_Color color_;
	vector<string> textLines;
	vector<Texture> textTextures_; //MAYBE NO HACE FALTA

	Uint8 alpha_;
};

