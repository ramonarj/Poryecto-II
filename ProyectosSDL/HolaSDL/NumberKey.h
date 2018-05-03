#pragma once
#include "Entity.h"
#include "ResourceManager.h"

class NumberKey :
	public Entity
{
public:
	NumberKey() {};
	NumberKey(SDL_Renderer * pRenderer, int value, int fil, int col, float edge, float space, float screen);
	~NumberKey();

	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	int getValue() { return value_; };
	bool clicked(int x, int y, Uint32 time);

private:
	SDL_Renderer * pRenderer_;
	ResourceManager* resource = nullptr;

	Texture * key_, *pressedKey_;
	SDL_Rect dest_, src;
	int value_;
	bool clicked_;
	string keyValue;

	Uint32 timeStarted = 0, timeOn = 300;
};

