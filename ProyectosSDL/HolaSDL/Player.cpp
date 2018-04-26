#include "Player.h"



Player::Player() :Character()
{
}

void Player::move(Entity* o)
{
	Vector2D pos = { o->getPosition().getX(), o->getPosition().getY() };
	Character::move(o);
}

void Player::handleInput(Entity* o, Uint32 time, const SDL_Event& event){}

void Player::render(Entity* o, Uint32 time) {}

void Player::saveToFile(Entity* o)
{
	ofstream file;
	file.open(FOLDER + SAVE_FOLDER + "player.pac");
	if (file.is_open())
	{
		o->saveEntity(o, file);
		file << life;
	}
	file.close();
}

void Player::loadToFile(Entity* o)
{
	ifstream file;
	file.open(FOLDER + SAVE_FOLDER + "player.pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
		o->loadEntity(o, file);

		file >> life;
	}

	file.close();
}

Player::~Player()
{
}

void Player::cure() {
	int auxi;
	auxi = int(maxLife_ * cureIndex_);
	life += auxi;
	if (life > maxLife_)
		life = maxLife_;
}