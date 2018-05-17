#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "Player.h"
#include "Enemy.h"
#include "checkML.h"


enum MessageId {
	PLAYER_INTERACTION,
	PLAYER_ENEMY_COLLISION
};

struct Message {
	Message(MessageId id) :
			id_(id) {
	}
	MessageId id_;
};

struct PlayerInteracts : Message {
	PlayerInteracts(Player* player): Message(PLAYER_INTERACTION), player_(player) {}
	Player* player_;
};

struct PlayerCollidesEnemy : Message {
	PlayerCollidesEnemy(Player* player, Enemy* enemy) : Message(PLAYER_ENEMY_COLLISION), player_(player), enemy_(enemy) {}
	Player* player_;
	Enemy* enemy_;
};

#endif /* MESSAGES_H_ */
