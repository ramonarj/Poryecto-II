#include "CarnePuaj.h"
#include "PlayState.h"
#include "MessageTrigger.h"


CarnePuaj::CarnePuaj(std::string interactMessage) : Interactible(interactMessage)
{
}


CarnePuaj::~CarnePuaj()
{
}

void CarnePuaj::interact(Entity* e) {
	if (acid_)
		PlayState::Instance()->removeEntity(e);
}

void CarnePuaj::update(Entity* e, Uint32 time) {
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();
	if (inventory == nullptr)
		inventory = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>();

	SDL_Rect playerRect = { int(player->getPosition().getX()), int(player->getPosition().getY()), int(player->getWidth()), int(player->getHeight()) };
	SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

	if (Collisions::RectRect(&playerRect, &thisRect)) {
		Item* acidInventory = nullptr;

		for (int i = 0; i < inventory->getInventory().size() && !acid_; i++)
		{
			Item* item = inventory->getInventory()[i]->getComponent<Item>();
			if (item != nullptr)
				if (item->getType() == ACID)
					acidInventory = item;
		}
		if (acidInventory != nullptr) {
			acid_ = true;
			e->getComponent<MessageTrigger>()->setMessage("'E' para usar el acido y quemar la masa de carne",
				"'Square/X' para usar el acido y quemar la masa de carne");
		}
		else {
			acid_ = false;
			e->getComponent<MessageTrigger>()->setMessage("Es necesario un potente acido para quemar la masa carne");
		}
	}
}