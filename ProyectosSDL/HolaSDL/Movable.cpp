#include "Movable.h"



Movable::Movable() : player_(nullptr)
{
}

Movable::Movable(Entity* player) : player_(player)
{
}

Movable::~Movable()
{
}

void Movable::update(Entity* e, Uint32 time) {
	SDL_Rect playerRect = player_->getRect();
	SDL_Rect movableRect = e->getRect();
	Vector2D playerdir = player_->getDirection();
	bool collision = Collisions::RectRect(&playerRect, &movableRect);

	if (collision && firstCollision)
	{
		movabledir = playerdir;
		firstCollision = false;
	}
	else if (!collision) {
		firstCollision = true;
	}
	/*movabledir.normalize();
	playerdir.normalize();*/
	if ((e->getVelocity().getX() == 0 && e->getVelocity().getY() == 0) &&
		((lastVel.getX() == 0 && lastVel.getY() != 0) || (lastVel.getX() != 0 && lastVel.getY() == 0))
		/*&& (player_->getVelocity().getX() != 0 || player_->getVelocity().getY() != 0)*/)
	{
		Vector2D pos(0, 0);
		Vector2D vel(0, 0);
		pos.setX(player_->getPosition().getX() - player_->getVelocity().getX());
		pos.setY(player_->getPosition().getY() - player_->getVelocity().getY());
		lastVel = vel;
		player_->setVelocity(vel);
		player_->setPosition(pos);
	}
	else {
		if (collision && (movabledir - playerdir).magnitude() < 1)
		{
			Vector2D pos = { e->getPosition().getX(), e->getPosition().getY() };
			Vector2D vel = { player_->getVelocity() };
			pos.setX(pos.getX() + vel.getX());
			pos.setY(pos.getY() + vel.getY());

			e->setVelocity(vel);
			lastVel = vel;
			e->setPosition(pos);
		}
	}
};