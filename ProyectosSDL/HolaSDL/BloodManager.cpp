#include "BloodManager.h"
#include "Game.h"



BloodManager::BloodManager() : bloodOn_(true)
{
	renderer_ = Game::Instance()->getRenderer(); //Renderer principal
	bloodText = Game::Instance()->getResourceManager()->getTexture("Blood");
	alpha_ = 0;
	destrect = RECT(0, 0,
		Game::Instance()->getWindowWidth(),
		Game::Instance()->getWindowHeight()
	);
	interCorto = 100;
	interLargo = 500;
}


BloodManager::~BloodManager()
{
}

void BloodManager::render(Entity * e, Uint32 time) {
	if (player_ == nullptr)
		player_ = Game::Instance()->getEntityWithComponent<Player>();
	
	int currentLife = player_->getComponent<Player>()->getLife();
	int maxlife = player_->getComponent<Player>()->getMaxLife();
	float bloodActiveNormal = maxlife*0.5;	//cantidad de vida para que se active la sangre de pantalla (vel normal)
	float bloodActiveFast = maxlife*0.2;	//cantidad de vida para que se active la sangre de pantalla (vel rápida)
	int alphaCorto = 50;
	int alphaLargo = 100;

	if (bloodOn_) {
		
		//Si la vida de elise esta igual o por debajo de 1/3 de la vida maxima
		if (currentLife <= bloodActiveNormal) {
			interCorto = 120;
			interLargo = 550;
		}
		
		//Si la vida de Elise esta igual o por debajo de 1/5 de la vida maxima los latidos van mas rápidos
		if (currentLife <= bloodActiveFast) {
			interCorto = 50;
			interLargo = 250;
		}
		if (player_->getComponent<Player>()->getInvincible() && pant) {
			SDL_SetRenderDrawColor(renderer_, COLOR(0xFFFFFFFF));
			SDL_RenderClear(renderer_);
			SDL_RenderPresent(renderer_);
			SDL_Delay(10);
			if (currentLife <= bloodActiveNormal) {
				SDL_SetRenderDrawColor(renderer_, COLOR(0xD50000FF));
				SDL_RenderClear(renderer_);
				SDL_RenderPresent(renderer_);
				SDL_Delay(10);
			}
			pant = false;
		}
		else if (!player_->getComponent<Player>()->getInvincible())
			pant = true;
		if (currentLife <= bloodActiveNormal) {
			if (time > actualTime_ + time_) {
				if (alpha_ > alphaCorto) {
					alpha_ = alphaCorto;
					time_ = interLargo;
				}
				else {
					alpha_ = alphaLargo;
					time_ = interCorto;
				}
				bloodText->ChangeAlphaValue(alpha_);

				actualTime_ = time;
			}
			bloodText->render(renderer_, destrect);
		}
	}
}

void BloodManager::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_b)
			bloodOn_ = !bloodOn_;
	}
}