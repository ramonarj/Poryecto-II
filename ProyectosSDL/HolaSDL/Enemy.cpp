#include "Enemy.h"
#include <iostream>
#include <math.h>
#include <algorithm>


Enemy::Enemy():player(nullptr), Character(){}

Enemy::Enemy(Entity* player, int life, int damage):player(player), Character(life, damage)
{
	Player* playerComp = player->getComponent<Player>();
	if (playerComp != nullptr)
		cout << "There's a player with life: " << playerComp->getLife() << endl;
}

void Enemy::move(Entity* o)
{
	//1.CÁLCULOS
	Entity* player = PlayState::Instance()->getPlayer();
	//Posición del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Persigue al jugador
	Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
	int distance = sqrt(pow(chaseVector.getX(), 2) + pow(chaseVector.getY(), 2));
	float alpha = float(abs(atan(chaseVector.getY() / chaseVector.getX())));
	int velMag = int(o->getVelocity().magnitude());

	////Ponemos la nueva velocidad
	//Vector2D vel{ cos(alpha) * velMag * chaseVector.getX() / abs(chaseVector.getX()), sin(alpha)* velMag * chaseVector.getY() / abs(chaseVector.getY()) };
	//cout << vel << endl;
	//o->setVelocity(vel);

	////Actualizamos a posicion(PONER ESTO EN CHARACTER)
	//pos.setX(pos.getX() + o->getVelocity().getX());
	//pos.setY(pos.getY() + o->getVelocity().getY());

	//2.VELOCIDAD
	Vector2D vel;
	//Movimiento en X
	if (pos.getX() < playerPos.getX())
		vel.setX(cos(alpha) * velMag);
	else if (pos.getX() > playerPos.getX())
		vel.setX(cos(alpha) * -velMag);

	//Movimiento en Y
	if (pos.getY() < playerPos.getY())
		vel.setY(velMag);
	else if (pos.getY()> playerPos.getY())
		vel.setY(-velMag);

	//cout << alpha << endl;

	//Actualizamos la velocidad
	o->setVelocity(vel);


	///3.DIRECCIÓN
	Vector2D dir;
	//Prioritaria en el eje X
	if (vel.getX() > 0)
		dir.setX(1);
	else
		dir.setX(-1);

	//Prioritaria en el eje Y
	if (vel.getY() > 0) 
		dir.setY(-1);
	else
		dir.setY(1);

	//Eje prioritario (solo tenemos en cuenta las direcciones (-1, 0), (1, 0), (0, -1) y (0, 1)
	if (abs(chaseVector.getX()) > abs(chaseVector.getY()))
		dir.setY(0);
	else
		dir.setX(0);

	o->setDirection(dir);

	//4.SE MUEVE
	Character::move(o);

	//5.COLISIONES
	//Lo pilla
	if (distance <= ALCANCE)
	{
		//De momento, ambos se hacen daño
		player->getComponent<Player>()->takeDamage(damage);
		this->takeDamage(player->getComponent<Player>()->getDamage());

		//Respawn-> HACER UN KNOCKBACK
		pos.setX(pos.getX() + 30);
		pos.setY(pos.getY() + 30);
		o->setPosition(pos);
	}
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	//Tanto él como el jugador están vivos
	if (isAlive() && player!=nullptr && player->getComponent<Player>()->isAlive())
		move(o);
	else
		o->setVelocity(Vector2D(0, 0));
}

Enemy::~Enemy()
{
}
