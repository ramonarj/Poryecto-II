#include "Player.h"



Player::Player() :Character(), coolDown_(false), coolDownOn_(0), coolDownTime_(1000), invincible_(false), invincibleOn_(0), invincibleTime_(3000), invincibleOnOff_(0),
				teleport_(false), numDoorToTeleport_(0), doorToTeleport_(nullptr)
{
}
Player::~Player()
{
}

void Player::move(Entity* o)
{
	Vector2D pos = { o->getPosition().getX(), o->getPosition().getY() };
	Character::move(o);
}

void Player::update(Entity * o, Uint32 time)
{
	coolDownAttack(time);
	invincible(o, time);
	Character::update(o, time);
}

void Player::handleInput(Entity* o, Uint32 time, const SDL_Event& event){}

void Player::render(Entity* o, Uint32 time) {}

void Player::saveToFile(Entity* o)
{
	ofstream file;
	file.open(SAVE_FOLDER + "player.pac");
	if (file.is_open())
	{
		o->saveEntity(o, file);
		file << life;
	}
	else
		cout << "Error al abrir el archivo de Guardado de Player" << endl;
	file.close();
}

void Player::loadToFile(Entity* o)
{
	ifstream file;
	file.open(SAVE_FOLDER + "player.pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
		o->loadEntity(o, file);

		file >> life;
	}
	else
		cout << "Error al abrir el archivo de Cargado de Player" << endl;

	file.close();
}

void Player::startCoolDown()
{
	coolDown_ = true;
	coolDownOn_ = SDL_GetTicks();
}

void Player::coolDownAttack(Uint32 time)
{
	if (coolDown_ && (coolDownOn_ + coolDownTime_ < time))
		coolDown_ = false;
}

void Player::startInvincible()
{
	invincible_ = true;
	invincibleOn_ = SDL_GetTicks();
	invincibleOnOff_ = SDL_GetTicks();
}

void Player::invincible(Entity* o, Uint32 time)
{
	if (invincible_ && (invincibleOn_ + invincibleTime_ < time))
	{
		invincible_ = false;
		o->getComponent<PlayerAnimationComponent>()->removeTransparency();
	}
	else if (invincible_ && (invincibleOnOff_ + invincibleTime_ / 20 < time))
	{
		o->getComponent<PlayerAnimationComponent>()->invincible();
		invincibleOnOff_ = SDL_GetTicks();
	}
}

void Player::startTeleport(Entity* e, int door, string ori)
{
	teleport_ = true;
	numDoorToTeleport_ = door;
	doorToTeleport_ = e;

	Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->setDoFade(true, 20);

	if (ori == "norte")oriDoorToTeleport_ = "sur";
	else if (ori == "sur")oriDoorToTeleport_ = "norte";
	else if (ori == "este")oriDoorToTeleport_ = "oeste";
	else if (ori == "oeste")oriDoorToTeleport_ = "este";
}


void Player::cure() {
	int auxi;
	auxi = int(maxLife_ * cureIndex_);
	life += auxi;
	if (life > maxLife_)
		life = maxLife_;
}