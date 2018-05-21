#pragma once
#include "Component.h"
#include "Game.h"
#include <string>

using namespace std;

typedef void CallBackOnClick(Game* game);

//class PlayState;

class Button : public Component{

private:
	Texture* texture_;
	SDL_Rect rect;
	string buttonType;

public:
	Button() {};
	Button(CallBackOnClick* callBack, Texture* texture, Vector2D pos);
	~Button();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);

	//virtual void loadFromFile(ifstream &archivo) {}; 
	//virtual void saveFromFile(ofstream &archivo) {}; 

	void MarkButton(bool value);
	CallBackOnClick* cbOnClick;
};

