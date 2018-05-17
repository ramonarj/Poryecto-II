#pragma once
#include "Component.h"
#include "checkML.h"

class Game;

class Credits : public Component {
private:
	//int spacing_;
	float velocity_;
	Texture* image_;

	//Font* font_;
	//SDL_Color color_;

	SDL_Renderer* renderer_;
	//vector<string> textLines;
	//vector<Texture> textTextures_; 

public:
	Credits(Game* game_, Texture* image, float velocity);
	~Credits();
	virtual void update(Entity* e, Uint32 time);
	virtual void render(Entity* e, Uint32 time);
};

