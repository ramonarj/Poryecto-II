#include "CarnePuaj.h"
#include "PlayState.h"
#include "MessageTrigger.h"
#include "CarnePuajAnimationRenderer.h"


CarnePuaj::CarnePuaj(std::string interactMessage) : Interactible(interactMessage), playerDir(0, 0), acid_(false)
{
}


CarnePuaj::~CarnePuaj()
{
}

void CarnePuaj::interact(Entity* e) {
	if (acid_)
	{
		e->getComponent<MessageTrigger>()->setMessage("", false);
		e->getComponent<CarnePuajAnimationRenderer>()->destroy();
	}
}

void CarnePuaj::update(Entity* e, Uint32 time) {
	if (player == nullptr)
		player = PlayState::Instance()->getPlayer();
	if (inventory == nullptr)
		inventory = Game::Instance()->getEntityWithComponent<Inventory>()->getComponent<Inventory>();

	SDL_Rect playerRect = { int(player->getPosition().getX() - player->getWidth() / 2), int(player->getPosition().getY() - player->getHeight() / 2), int(2 * player->getWidth()), int(2 * player->getHeight()) };
	SDL_Rect thisRect = { int(e->getPosition().getX()), int(e->getPosition().getY()), int(e->getWidth()), int(e->getHeight()) };

	if (player->getPosition().getX() + player->getWidth() < e->getPosition().getX() || player->getPosition().getX() > e->getPosition().getX() + e->getWidth())
		playerDir.set(Vector2D(player->getDirection().getX(), player->getDirection().getY()));

	if (!playerCanMove(e) && Collisions::RectRect(&playerRect, &thisRect)) {
		player->setPosition(Vector2D(player->getPosition().getX() - player->getVelocity().getX(), player->getPosition().getY() - player->getVelocity().getY()));
		Item* acidInventory = nullptr;

		for (int i = 0; i < inventory->getInventory().size() && !acid_; i++)
		{
			Item* item = inventory->getInventory()[i]->getComponent<Item>();
			if (item != nullptr)
				if (item->getType() == ACID)
				{
					acidInventory = item;
					acid_ = true;
				}
		}
		if (acid_) {
			e->getComponent<MessageTrigger>()->setMessage("'E' para usar el acido y quemar la masa de carne",
				"'Square/X' para usar el acido y quemar la masa de carne");
		}
		else {
			e->getComponent<MessageTrigger>()->setMessage("Es necesario un potente acido para quemar la masa de carne", true);
		}

	}
}

bool CarnePuaj::playerCanMove(Entity* e)
{
	PlayerAnimationComponent* animComp = player->getComponent<PlayerAnimationComponent>();
	return (animComp->getLastDir().getX() > 0 && playerDir.getX() < 0 &&  player->getPosition().getX() + player->getWidth() > e->getPosition().getX()
		|| animComp->getLastDir().getX() < 0 && playerDir.getX() > 0 && player->getPosition().getX() < e->getPosition().getX() + e->getWidth());
}
