#include "Enemy.h"
#include <iostream>
#include <math.h>
#include <algorithm>


Enemy::Enemy():player(nullptr), rango(DEFAULT_RANGE), relaxTime(0), reloading(false), Character(){}

Enemy::Enemy(Vector2D vel): player(nullptr), rango(DEFAULT_RANGE), relaxTime(0), reloading(false), Character()
{
	velMag = vel.magnitude();
}

Enemy::Enemy(Entity* player, int life, int damage, int rango):player(player), Character(life, damage), rango(rango)
{
}

void Enemy::move(Entity* o)
{
	//1.CÁLCULOS
	//Posición del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Persigue al jugador
	Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
	int distance = sqrt(pow(chaseVector.getX(), 2) + pow(chaseVector.getY(), 2));
	float alpha = float(abs(atan(chaseVector.getY() / chaseVector.getX())));


	////Ponemos la nueva velocidad
	//Vector2D vel{ cos(alpha) * velMag * chaseVector.getX() / abs(chaseVector.getX()), sin(alpha)* velMag * chaseVector.getY() / abs(chaseVector.getY()) };
	//cout << vel << endl;
	//o->setVelocity(vel);

	////Actualizamos a posicion(PONER ESTO EN CHARACTER)
	//pos.setX(pos.getX() + o->getVelocity().getX());
	//pos.setY(pos.getY() + o->getVelocity().getY());

	//2.VELOCIDAD
	Vector2D vel;
	int difY = 100;
	//Movimiento en X
	if (pos.getX() < playerPos.getX())
		vel.setX(cos(alpha) * velMag);
	else if (pos.getX() > playerPos.getX())
		vel.setX(cos(alpha) * -velMag);

	//Movimiento en Y
	if (pos.getY() < playerPos.getY())
		vel.setY(velMag);
	else if (pos.getY() > playerPos.getY())
		vel.setY(-velMag);


	//Actualizamos la velocidad
	o->setVelocity(vel);


	///3.DIRECCIÓN
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
	//Posición del jugador y del enemigo
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
		//El que pille recibirá daño y knockback
		//El player le ataca
		if (player->getComponent<Player>()->getAttacking())
		{
			chaseVector.setX(-chaseVector.getX());
			chaseVector.setY(-chaseVector.getY());
			Character::knockBack(o, chaseVector);
			this->takeDamage(player->getComponent<Player>()->getDamage());
		}
		//Él ataca
		else
		{
			Character::attacking = true;
			Character::knockBack(player, chaseVector);
			player->getComponent<Player>()->takeDamage(damage);
		}
		reloading = true;
	}
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	//Tanto él como el jugador están vivos
	if (isAlive() && playerInRange(o) && !reloading)
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
	//Muere	
	else
		o->setVelocity(Vector2D(0, 0));
}

Enemy::~Enemy()
{
}
