#include "Enemy.h"
#include <iostream>
#include <math.h>
#include <algorithm>


Enemy::Enemy():player(nullptr), rango(DEFAULT_RANGE), relaxTime(0), reloading(false), Character(), dead(false), deadOn_(0), deadTime_(0), push (20) {}


void Enemy::move(Entity* o)
{
	//1.C�LCULOS
	//Posici�n del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Persigue al jugador
	Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
	int distance = sqrt(pow(chaseVector.getX(), 2) + pow(chaseVector.getY(), 2));
	float alpha = float(abs(atan(chaseVector.getY() / chaseVector.getX())));


	//2.VELOCIDAD
	Vector2D vel;

	double aux = 0;
	double dif = 3;

	if (numEnemy_ == 1) aux = -30;
	else if (numEnemy_ == 2) aux = 20;

	if (!o->getComponent<Character>()->getKnockBack())
	{
		//Movimiento en X
		if (pos.getX() < playerPos.getX() - dif)
			vel.setX(cos(alpha) * velMag);
		else if (pos.getX() > playerPos.getX() + dif)
			vel.setX(cos(alpha) * -velMag);
		else
			vel.setX(0);

		//Movimiento en Y

		if (numEnemy_ == 1) aux = -30;
		else if (numEnemy_ == 2) aux = 20;

		if (pos.getY() - aux < playerPos.getY() - dif)
			vel.setY(velMag);
		else if (pos.getY() - aux > playerPos.getY() + dif)
			vel.setY(-velMag);
		else
			vel.setY(0);

		//Actualizamos la velocidad
		o->setVelocity(vel);
	}


	///3.DIRECCI�N
	Vector2D dir;
	//Prioritaria en el eje X
	dir.setX((vel.getX() > 0) ? 1 : -1); //Vaya guapo el ternary operator
	//Prioritaria en el eje Y
	dir.setY((vel.getY() > 0) ? -1 : 1);

	//Eje prioritario (solo tenemos en cuenta las direcciones (-1, 0), (1, 0), (0, -1) y (0, 1)
	if (abs(chaseVector.getX()) > abs(chaseVector.getY()))
		dir.setY(0);
	else
		dir.setX(0);

	o->setDirection(dir);


	//4.SE MUEVE
	Character::move(o);


	//5.COLISIONES
	checkCollisions(o, chaseVector);
}

bool Enemy::playerInRange(Entity * o)
{
	//Posici�n del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Persigue al jugador
	Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
	int distance = sqrt(pow(chaseVector.getX(), 2) + pow(chaseVector.getY(), 2));

	return(player != nullptr && player->getComponent<Player>()->isAlive() && distance < rango);
}

void Enemy::checkCollisions(Entity* o, Vector2D chaseVector)
{
	SDL_Rect playerRect = player->getRect();
	SDL_Rect enemyRect = o->getRect();
	if (Collisions::RectRect(&playerRect, &enemyRect))
	{
		//El que pille recibir� da�o y knockback
		//El player le ataca
		if (player->getComponent<Player>()->getAttacking())
		{
			chaseVector.setX(-chaseVector.getX());
			chaseVector.setY(-chaseVector.getY());
			Character::knockBack(o, Vector2D(player->getComponent<AnimationRenderer>()->getLastDir().getX()* push, player->getComponent<AnimationRenderer>()->getLastDir().getY() * push));
			this->takeDamage(player->getComponent<Player>()->getDamage());
		}
		//�l ataca
		else
		{
			setAttacking(true);

			Character::knockBack(player, Vector2D(o->getVelocity().getX() * push, o->getVelocity().getY() * push));

			player->getComponent<Player>()->takeDamage(damage);
		}
		reloading = true;
	}
}

void Enemy::bringMeToLife(Uint32 time)
{
	if (!isAlive()) {
		if (dead && (deadOn_ + deadTime_ < time)) {
			dead = false;
			setAlive();
		}
	}
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	//Tanto �l como el jugador est�n vivos
	if (o->getComponent<Character>()->getKnockBack())
	{
		Character::update(o, time);
	}
	else if (isAlive() && playerInRange(o) && !reloading)
		move(o);
	//Recargando
	else if (reloading)
	{
		o->setVelocity(Vector2D(0, 0));
		relaxTime++;
		if (relaxTime >= COOLDOWN)
		{
			relaxTime = 0;
			reloading = false;
		}
	}
	else if (!playerInRange(o))
		o->setVelocity(Vector2D(0, 0));
	//Muere	
	else {
		if (!dead) {
			dead = true;
			deadOn_ = time;
			deadTime_ = 20000;
			o->setVelocity(Vector2D(0, 0));
		}
	}

	bringMeToLife(time);
}

void Enemy::load(int numEnemy)
{	
	numEnemy_ = numEnemy;
	Vector2D vel;
	if (numEnemy == 1)
		vel.set(Vector2D(1.0, 0.0));
	else if (numEnemy == 2)
		vel.set(Vector2D(2.0, 0.0));
	else if (numEnemy == 3)
		vel.set(Vector2D(3.0, 0.0));

	velMag = vel.magnitude();
}

Enemy::~Enemy()
{
}
