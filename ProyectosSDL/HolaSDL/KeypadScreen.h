#pragma once
#include "Entity.h"
#include "ResourceManager.h"
class KeypadScreen :
	public Entity
{
public:
	KeypadScreen() {};
	KeypadScreen(SDL_Renderer* pRenderer);
	void setSequence(string n){
		sequence = n;
	};
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time);
	~KeypadScreen();
private:
	pair <int, int> numero(char s);
	string sequence;
	SDL_Renderer* pRenderer_;
	ResourceManager* resource = nullptr;
	Texture* image_;
	SDL_Rect dest, src;
};

