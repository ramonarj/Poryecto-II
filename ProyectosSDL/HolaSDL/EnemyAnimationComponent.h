#pragma once
#include "Component.h"
#include "Entity.h"
#include "Game.h"

class EnemyAnimationComponent :
	public Component
{
public:
	EnemyAnimationComponent();
	EnemyAnimationComponent(Uint32 enemyType, Texture * moving, Texture * iddle, Texture * attacking, Texture * diying, Texture * resurrecting,
		Uint32 cooldown, Uint32 iddleFrames, Uint32 movementFrames, Uint32 attackingFrames, Uint32 diyingFrames, Uint32 resurrectingFrames);
	virtual ~EnemyAnimationComponent();
	virtual void render(Entity* o, Uint32 time);
	virtual void update(Entity* o, Uint32 time) {};
	virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event) {};
	Vector2D getLastDir() { return lastDir; };

	//void setFramesToZero() { attackingFrames_ = 0; };


private:
	Uint32 enemyType_ = -1; //Enemy 1, 2 or 3

	Texture * iddle_ = nullptr;
	Texture * moving_ = nullptr;
	Texture * attacking_ = nullptr;
	Texture * diying_ = nullptr;
	Texture * resurrecting_ = nullptr;

	Uint32 movementFrames_;
	Uint32 iddleFrames_;
	Uint32 attackingFrames_;
	Uint32 diyingFrames_;
	Uint32 resurrectingFrames_;

	Uint32 directions_=4;

	Uint32 actualTime_=0;
	Uint32 actualFrameMoving_ = 0;
	Uint32 actualFrameAttacking_ = 0;
	Uint32 actualFrameIddle_ = 0;
	Uint32 actualFrameDiying_ = 0;

	Uint32 actualFrameResurrecting_ = 0;

	Uint32 cooldown_;
	Uint32 cooldownIddle_;

	Uint32 widthFrame_;
	Uint32 heightFrame_;

	Vector2D lastDir;

	int dir(Entity* o);
	int dirIddle(Entity* o);

	bool attackInProgress_ = false;
};

