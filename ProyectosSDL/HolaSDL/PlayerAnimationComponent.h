#pragma once
#include "Component.h"
#include "Entity.h"
#include "Game.h"

class PlayerAnimationComponent :
	public Component
{
public:
	PlayerAnimationComponent();
	PlayerAnimationComponent(Texture * iddle, Texture * moving, Texture * attackingCrowbar, Texture * attackingPipe, Texture * Crutch, Texture * attackingAxe, Texture * diying, Texture * awakening,
		Uint32 cooldown, Uint32 iddleFrames, Uint32 movementFrames, Uint32 attackingFrames, Uint32 diyingFrames, Uint32 awakeningFrames);
	virtual ~PlayerAnimationComponent();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};
	Vector2D getLastDir() { return lastDir; };

	void invincible();
	void removeTransparency();



private:

	Texture * iddle_ = nullptr;
	Texture * moving_ = nullptr;
	Texture * attackingCrowbar_ = nullptr, * attackingPipe_ = nullptr, * attackingCrutch_ = nullptr, * attackingAxe_ = nullptr;
	Texture * attacking_;
	vector<Texture*> attackingTextures_;
	Texture * diying_ = nullptr;
	Texture * awakening_ = nullptr;

	Uint32 movementFrames_;
	Uint32 iddleFrames_;
	Uint32 attackingFrames_;
	Uint32 diyingFrames_;
	Uint32 awakeningFrames_;

	Uint32 directions_ = 4;

	Uint32 actualTime_ = 0;
	Uint32 actualFrameMoving_ = 0;
	Uint32 actualFrameAttacking_ = 0;
	Uint32 actualFrameIddle_ = 0;
	Uint32 actualFrameDiying_ = 0;

	Uint32 actualFrameAwakening_ = 0;

	Uint32 cooldown_;
	Uint32 cooldownIddle_;

	Uint32 widthFrame_;
	Uint32 heightFrame_;

	Vector2D lastDir;

	int weapon(Entity* o);
	int dir(Entity* o);
	int dirIddle(Entity* o);
	bool soundActive = false;

	int weaponId = -1;

	bool attackInProgress_ = false;

	Uint8 alpha_;
};

