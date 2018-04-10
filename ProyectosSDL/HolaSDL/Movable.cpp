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
	if (collision && (movabledir - playerdir).magnitude() < 1)
	{
		Vector2D pos = { e->getPosition().getX(), e->getPosition().getY() };

		pos.setX(pos.getX() + player_->getVelocity().getX());
		pos.setY(pos.getY() + player_->getVelocity().getY());

		e->setPosition(pos);
	}

};