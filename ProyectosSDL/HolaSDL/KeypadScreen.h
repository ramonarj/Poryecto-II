#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "checkML.h"


class KeypadScreen :
	public Entity
{
public:
	KeypadScreen() {};
	KeypadScreen(SDL_Renderer* pRenderer, float h, float w);
	void setSequence(string n){
		sequence = n;
	};
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	~KeypadScreen();
private:
	Uint32 timeOn = 0, delta = 500;
	bool on = true;
	pair <int, int> numero(char s);
	string sequence;
	SDL_Renderer* pRenderer_;
	ResourceManager* resource = nullptr;
	Texture* image_;
	SDL_Rect dest, src;
};

