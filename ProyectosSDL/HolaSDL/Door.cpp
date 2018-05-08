#include "Door.h"
#include "Game.h"
#include "PlayState.h"
#include "MessageTrigger.h"

Door::Door(Entity* thisDoor) : player(nullptr), inventory(nullptr), compContainer(nullptr),
	compInvent(nullptr), itemKey(nullptr), doorNum_(0), needKey_(false), 
	collidableDoor_(false), messageChanged_(false), thisDoor_(thisDoor),
	messageRenderer(nullptr), messageTimer(nullptr) {
}


Door::~Door() {
}

void Door::interact(Entity * e)
{
	int n = 0;
	if (collidableDoor_) 
	{
		if (needKey_)
		{
			setNeedKey();
		}
		else
		{
			if (canTeleport())
			{
				PlayState::Instance()->getPlayer()->getComponent<Player>()->startTeleport(e, doorNum_, ori_);
				Game::Instance()->getResourceManager()->getSound("DoorSound")->play();
			}
		}
	}
}

void Door::load(int numero, string ori, int needKey, int collidableDoor, string zoneName)
{
	doorNum_ = numero;
	ori_ = ori;
	needKey_ = needKey;
	if (needKey_)
		thisDoor_->getComponent<MessageTrigger>()->setMessage("Necesitas una llave");
	collidableDoor_ = collidableDoor;
	zoneName_ = zoneName;
}

bool Door::canTeleport()
{
	PlayerAnimationComponent* animPlayer = player->getComponent<PlayerAnimationComponent>();

	return ((ori_ == "norte" && animPlayer->getLastDir().getY() == 1)
		|| (ori_ == "sur" && animPlayer->getLastDir().getY() == -1)
		|| (ori_ == "este" && animPlayer->getLastDir().getX() == 1)
		|| (ori_ == "oeste" && animPlayer->getLastDir().getX() == -1));
}

void Door::teleport()
{
	doors = (*Game::Instance()->stateMachine_.currentState()->getDoors());
	list<Entity*>::const_iterator it = doors.begin();
	bool puertEncontrada = false;

	while (it != doors.end() && !puertEncontrada)
	{
		if (PlayState::Instance()->getPlayer()->getComponent<Player>()->getDoorToTeleport() != (*it))
		{
			Door* doorComp = (*it)->getComponent<Door>();
			if (doorComp->isCollidable() && PlayState::Instance()->getPlayer()->getComponent<Player>()->getNumDoor() == doorComp->getDoorNum() 
				&& PlayState::Instance()->getPlayer()->getComponent<Player>()->getOriDoor() == doorComp->getOri())
			{
				if (doorComp->getOri() == "norte")
					player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2 - player->getWidth() / 2,
					(*it)->getPosition().getY() + (*it)->getHeight() / 10));

				else if (doorComp->getOri() == "sur")
					player->setPosition(Vector2D(((*it)->getPosition().getX() + (*it)->getWidth() / 2) - player->getWidth() / 2,
					(*it)->getPosition().getY() - player->getHeight() / 2));

				else if (doorComp->getOri() == "este")
					player->setPosition(Vector2D((*it)->getPosition().getX() - player->getWidth() / 2,
					(*it)->getPosition().getY()));

				else if (doorComp->getOri() == "oeste")
					player->setPosition(Vector2D((*it)->getPosition().getX() + (*it)->getWidth() / 2,
					(*it)->getPosition().getY()));

				if (isCollidable()) {
					std::string name = (*it)->getComponent<Door>()->getZoneName();
					cout << name << endl;
					if (name != "") {
						messageRenderer->display(name,
							Game::Instance()->getWindowWidth() / 2, Game::Instance()->getWindowHeight() / 8);
						messageTimer->start(4);
					}
				}
				PlayState::Instance()->getPlayer()->getComponent<Player>()->setTeleport(false);

				if (doorComp->getZoneName() == "SAFE ROOM")
					player->getComponent<Player>()->setLastSRPos(player->getPosition());

				puertEncontrada = true;
			}
		}
		it++;
	}
}

bool Door::getNeedKey()
{
	return needKey_;
}

void Door::setNeedKey()
{
	//inventory = Game::Instance()->getEntityWithComponent<Inventory>();
	compContainer = inventory->getComponent<ItemContainer>();
	//compInvent = inventory->getComponent<Inventory>();

	if (!compInvent->getKeys().empty()) {
		int i = 0;
		while (i < compInvent->getKeys().size() && needKey_)
		{
			if (compInvent->getKeys()[i]->getComponent<Key>()->getDoorId() == doorNum_) {
				thisDoor_->getComponent<MessageTrigger>()->setMessage("'E' para abrir", "'Square/X' para abrir");
				compInvent->removeKey(doorNum_);
				openDoor();
			}
			else
				i++;
		}
	}
}

void Door::openDoor()
{
	doors = (*Game::Instance()->stateMachine_.currentState()->getDoors());
	for (list<Entity*>::const_iterator it = doors.begin(); it != doors.end(); it++)
	{
		Door* doorComp = (*it)->getComponent<Door>();

		if (doorComp->getNeedKey()) {
			if (doorNum_ == doorComp->getDoorNum())
				doorComp->keyFalse();
		}
	}
}

void Door::keyFalse()
{
	needKey_ = false;
}

bool Door::isCollidable()
{
	return collidableDoor_;
}

void Door::update(Entity * e, Uint32 time) {
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();
	if (inventory == nullptr)
		inventory = Game::Instance()->getEntityWithComponent<Inventory>();
	if (compInvent == nullptr)
		compInvent = inventory->getComponent<Inventory>();
	if (messageRenderer == nullptr)
	{
		messageRenderer = PlayState::Instance()->getZoneMessageRenderer()->getComponent<MessageRenderer>();
		messageRenderer->setFont(Game::Instance()->getResourceManager()->getFont("VCR_OSD_MONO_32"));
	}
	if (messageTimer == nullptr)
		messageTimer = PlayState::Instance()->getZoneMessageRenderer()->getComponent<MessageTimer>();

	if (needKey_ && !messageChanged_) {
		SDL_Rect playerRect = { int(player->getPosition().getX()), int(player->getPosition().getY()), int(player->getWidth()), int(player->getHeight()) };
		SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

		if (Collisions::RectRect(&playerRect, &thisRect)) {
			if (!compInvent->getKeys().empty()) {
				int i = 0;
				bool found = false;
				while (i < compInvent->getKeys().size() && !found)
				{
					if (compInvent->getKeys()[i]->getComponent<Key>()->getDoorId() == doorNum_) {
						thisDoor_->getComponent<MessageTrigger>()->setMessage("'E' para usar la llave", "'Square/X' para usar la llave");
						messageChanged_ = true;
						found = true;
					}
					else
						i++;
				}
			}
		}
	}
	else if (!messageChanged_) {
		thisDoor_->getComponent<MessageTrigger>()->setMessage("'E' para abrir", "'Square/X' para abrir", false);
		messageChanged_ = true;
	}

	if (PlayState::Instance()->getPlayer()->getComponent<Player>()->getTeleport() &&
		Game::Instance()->getEntityWithComponent<FadeManager>()->getComponent<FadeManager>()->getAlphaFade() == MAX_FADE_ALPHA)
	{
		teleport();
	}
}

void Door::saveToFile(Entity* o)
{
	ofstream file;
	file.open(SAVE_FOLDER + "Door/door" + to_string(doorNum_) + ".pac");
	if (file.is_open())
	{
		file << needKey_;
	}
	file.close();
}

void Door::loadToFile(Entity* o)
{
	ifstream file;
	file.open(SAVE_FOLDER + "Door/door" + to_string(doorNum_) + ".pac");

	//Vemos si existe el archivo
	if (file.is_open())
	{
		file >> needKey_;
	}

	file.close();
}

