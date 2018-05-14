#pragma once
#include "Component.h"

class CarnePuajAnimationRenderer :
	public Component
{
public:
	CarnePuajAnimationRenderer(Texture* carnePuaj, Texture* carnePDestroyed, int cooldown, int carneFrames, int destroyedFrames);
	~CarnePuajAnimationRenderer();

	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};

	void destroy() {
		destroyed_ = true;
		cont = 0;
	};
	bool getDestroyed() {
		return finished_;
	};

private:
	SDL_Renderer* pRenderer_;
	Uint32 actualTime_= 0;
	bool destroyed_, finished_;
	Texture * image_, * imageDestroyed_;
	SDL_Rect dest;
	SDL_Rect clip;
	int cooldown_ = 0;
	int frames_, destroyedFrames_, cont;
};

