#include "Enemy.h"
#include <iostream>
#include <math.h>
#include <algorithm>


Enemy::Enemy():player(nullptr), rango(DEFAULT_RANGE), relaxTime(0), reloading(false), Character(), dead(false), deadOn_(0), deadTime_(0), push (25) {}


void Enemy::revive()
{
	resurecting = false;
	dead = false;
	setAlive();
}

void Enemy::punch(Entity* o)
{
	SDL_Rect playerRect = player->getRect();
	SDL_Rect enemyRect = o->getRect();
	//chaseVector_ = { player->getPosition().getX() - myself->getPosition().getX(), player->getPosition().getY() - myself->getPosition().getY() };

	//Comprobamos si estamos dentro todavia del enemigo
	if (Collisions::RectRect(&playerRect, &enemyRect))
	{
		if (player->getComponent<Player>()->getAttacking() && player->getComponent<Player>()->getPunch())
			{
				/*chaseVector_.setX(-chaseVector_.getX());
				chaseVector_.setY(-chaseVector_.getY());*/
				Character::knockBack(o, Vector2D(player->getComponent<PlayerAnimationComponent>()->getLastDir().getX()* push, player->getComponent<PlayerAnimationComponent>()->getLastDir().getY() * push));
				this->takeDamage(player->getComponent<Player>()->getDamage());
			}
			//�l ataca solo si está vivo y si lo está el player
			else if (isAlive() && player->getComponent<Character>()->isAlive())
			{
				Character::knockBack(player, Vector2D(o->getDirection().getX() * push, o->getDirection().getY() * push));
				player->getComponent<Player>()->takeDamage(damage);
				player->getComponent<Player>()->startInvincible();
			}
		
	}
}

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

	if (numEnemy_ == 1) aux = (-o->getHeight() / 4);
	else if (numEnemy_ == 2) aux = (o->getHeight() / 6);
	else if (numEnemy_ == 3) aux = (o->getHeight() / 3);

	if (!o->getComponent<Character>()->getKnockBack())
	{
		//Movimiento en X
		if (pos.getX() < playerPos.getX())
			vel.setX(cos(alpha) * velMag * getDeltaTime() / 4);
		else if (pos.getX() > playerPos.getX())
			vel.setX(cos(alpha) * -velMag * getDeltaTime() / 4);
		else
			vel.setX(0);

		//Movimiento en Y

		if (pos.getY() - aux < playerPos.getY() - dif)
			vel.setY(velMag * getDeltaTime() / 4);
		else if (pos.getY() - aux > playerPos.getY() + dif)
			vel.setY(-velMag * getDeltaTime() / 4);
		else
			vel.setY(0);

		if (vel.getX() != 0 && vel.getY() != 0)
		{
			vel.setX(vel.getX() * (sqrt(2) / 4) * getDeltaTime() / 4);
			vel.setY(vel.getY() * (sqrt(2) / 4) * getDeltaTime() / 4);
		}

		/*if (numEnemy_ == 3 && o->getDirection().getX() == 0 && o->getDirection().getY() == 1)
			cout << "Hola" << endl;*/

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
	if (vel.getX() == 0 || vel.getY() == 0)
	{
		if (vel.getX() == 0) dir.setX(0);
		else dir.setY(0);
	}
	else
	{
		if (abs(chaseVector.getX()) > abs(chaseVector.getY())) dir.setY(0);
		else dir.setX(0);
	}

	o->setDirection(dir);


	//4.SE MUEVE
	Character::move(o);
}

bool Enemy::playerInRange(Entity * o)
{
	//Posici�n del jugador y del enemigo
	Vector2D pos{ o->getPosition().getX(), o->getPosition().getY() };
	Vector2D playerPos{ player->getPosition().getX(), player->getPosition().getY() };

	//Persigue al jugador
	Vector2D chaseVector{ playerPos.getX() - pos.getX(), playerPos.getY() - pos.getY() };
	int distance = sqrt(pow(chaseVector.getX(), 2) + pow(chaseVector.getY(), 2));

	return(player != nullptr && player->getComponent<Player>()->isAlive() && distance < rango && !player->getComponent<Player>()->getAwakening());	
}

void Enemy::checkCollisions(Entity* o)
{
	SDL_Rect playerRect = player->getRect();
	SDL_Rect enemyRect = o->getRect();
	SDL_Rect internEnemyRect;

	internEnemyRect.x = enemyRect.x + enemyRect.w / 4;
	internEnemyRect.y = enemyRect.y + enemyRect.h / 6;
	internEnemyRect.w = enemyRect.w / 2;
	internEnemyRect.h = enemyRect.h * 2 / 3;

	bool effectDone = false;

	if (Collisions::RectRect(&playerRect, &enemyRect))
	{
		//El que pille recibir� da�o y knockback
		//El player le ataca
		if (player->getComponent<Player>()->getAttacking() && isAlive() && player->getComponent<Player>()->getPunch())
		{
			/*chaseVector.setX(-chaseVector.getX());
			chaseVector.setY(-chaseVector.getY());*/
			Character::knockBack(o, Vector2D(player->getComponent<PlayerAnimationComponent>()->getLastDir().getX()* push, player->getComponent<PlayerAnimationComponent>()->getLastDir().getY() * push));
			this->takeDamage(Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>()->currentWeapon()->getComponent<Weapon>()->getDamage());
			if (enemyType_ == -1) enemyType_ = o->getComponent<EnemyAnimationComponent>()->getType();

			if (enemyType_ == 1)
			{
				Game::Instance()->getResourceManager()->getSound("Monster1HitSound")->play();
			}
			else if (enemyType_ == 2)
			{
				Game::Instance()->getResourceManager()->getSound("Monster2HitSound")->play();
			}
			else if (enemyType_ == 3)
			{
				Game::Instance()->getResourceManager()->getSound("Monster3DeadSound")->play();
			}
			Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>()->currentWeapon()->getComponent<Weapon>()->attack();

			effectDone = true;
		
		}
		//�l ataca solo si está vivo y si lo está el player
		else if (isAlive() && player->getComponent<Character>()->isAlive() && !reloading && !player->getComponent<Player>()->getInvincible())
		{
 			/*chaseVector_ = chaseVector;*/
			setAttacking(true);

			//Character::knockBack(player, Vector2D(o->getDirection().getX() * push, o->getDirection().getY() * push));	//Si se pone este knockback aqui se empuja al player antes de colpear
			//player->getComponent<Player>()->startInvincible();

			reloading = true;
			effectDone = true;
		}
	}

	if (!pushed_ && Collisions::RectRect(&playerRect, &internEnemyRect))
	{
		if (isAlive() && player->getComponent<Character>()->isAlive()) 
		{
			setBlockDir(player);		
			Character::knockBack(player, Vector2D(o->getDirection().getX() * push, o->getDirection().getY() * push));
			pushed_ = true;
		}
	}
	else if (pushed_) pushed_ = false;
}

void Enemy::bringMeToLife(Uint32 time)
{
	if (!isAlive()) {
		if (dead && !resurecting && (deadOn_ + deadTime_ < time)) {
			resurecting = true;
		}
	}
}

void Enemy::handleInput(Entity* o, Uint32 time, const SDL_Event& event) {}
void Enemy::render(Entity* o, Uint32 time) {}

void Enemy::update(Entity * o, Uint32 time)
{
	if (myself == nullptr)
		myself = o;

	if (isAlive()) {
		//chaseVector_ = { player->getPosition().getX() - myself->getPosition().getX(), player->getPosition().getY() - myself->getPosition().getY() };
		checkCollisions(o);
	}

	//Tanto �l como el jugador est�n vivos
	if (o->getComponent<Character>()->getKnockBack() && isAlive())
	{
		Character::update(o, time);
	}
	else if (isAlive() && playerInRange(o) && !reloading)
		move(o);
	else if (isAlive() && !playerInRange(o) && !reloading)
		o->setVelocity(Vector2D(0, 0));
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
	/*else if (!playerInRange(o) && isAlive())
		o->setVelocity(Vector2D(0, 0));*/
	//Muere	
	else if (!isAlive()) {
		if (!dead) {
			dead = true;
			deadOn_ = time;
			deadTime_ = 20000;
		}
		o->setVelocity(Vector2D(0, 0));
	}

	bringMeToLife(time);
}

void Enemy::saveToFile(Entity* o)
{
	ofstream file;
	file.open(SAVE_FOLDER + "Enemy/enemy" + to_string(numFile_) + ".pac");
	if (file.is_open())
	{
		o->saveEntity(o, file);
	}
	file.close();
}

void Enemy::loadToFile(Entity* o)
{
	ifstream file;
	file.open(SAVE_FOLDER + "Enemy/enemy" + to_string(numFile_) + ".pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
		o->loadEntity(o, file);
	}

	file.close();
}

void Enemy::load(int numEnemy, int numEnemyFile)
{	
	numEnemy_ = numEnemy;
	numFile_ = numEnemyFile;
	Vector2D vel;
	if (numEnemy == 1)
	{
		vel.set(Vector2D((PLAYER_VEL - (PLAYER_VEL / 2)) * Camera::Instance()->getZoom(), 0.0));
		damage = 4;
		maxLife_ = life = 3;
	}
	else if (numEnemy == 2)
	{
		vel.set(Vector2D((PLAYER_VEL) * Camera::Instance()->getZoom(), 0.0));
		damage = 2;
		maxLife_ = life = 3;
	}
	else if (numEnemy == 3)
	{
		vel.set(Vector2D((PLAYER_VEL + (PLAYER_VEL / 15)) * Camera::Instance()->getZoom(), 0.0));
		damage = 1;
		maxLife_ = life = 2;
	}

	velMag = vel.magnitude();
}

Enemy::~Enemy()
{
}

void Enemy::setBlockDir(Entity* p) {

	int horizontal = 0;
	int vertical = 0;

	horizontal = p->getDirection().getX();
	vertical = p->getDirection().getY();

	if(horizontal==0 && vertical==1){
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(1);
		p->getComponent<ControllerInputComponent>()->setDirBlock(1);
	}
	else if (horizontal == 1 && vertical == 1) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(2);
		p->getComponent<ControllerInputComponent>()->setDirBlock(2);
	}
	else if (horizontal == 1 && vertical == 0) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(3);
		p->getComponent<ControllerInputComponent>()->setDirBlock(3);
	}
	else if (horizontal == 1 && vertical == -1) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(4);
		p->getComponent<ControllerInputComponent>()->setDirBlock(4);
	}
	else if (horizontal == 0 && vertical == -1) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(5);
		p->getComponent<ControllerInputComponent>()->setDirBlock(5);
	}
	else if (horizontal == -1 && vertical == -1) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(6);
		p->getComponent<ControllerInputComponent>()->setDirBlock(6);
	}
	else if (horizontal == -1 && vertical == 0) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(7);
		p->getComponent<ControllerInputComponent>()->setDirBlock(7);
	}
	else if (horizontal == -1 && vertical == 1) {
		p->getComponent<KeyBoardInputComponent>()->setDirBlock(8);
		p->getComponent<ControllerInputComponent>()->setDirBlock(8);
	}

}
