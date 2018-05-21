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
}


BloodManager::~BloodManager()
{
}

void BloodManager::render(Entity * e, Uint32 time) {
	if (player_ == nullptr)
		player_ = Game::Instance()->getEntityWithComponent<Player>();

	Uint32 interPositivo, interNegativo;
	int currentLife = player_->getComponent<Player>()->getLife();
	int maxlife = player_->getComponent<Player>()->getMaxLife();
	float bloodActiveNormal = (int)ceil(maxlife*0.3);	//cantidad de vida para que se active la sangre de pantalla (vel normal)
	float bloodActiveFast = (int)ceil(maxlife*0.2);	//cantidad de vida para que se active la sangre de pantalla (vel rápida)

	if (bloodOn_) {

		//Si la vida de elise esta igual o por debajo de 1/3 de la vida maxima
		if (currentLife <= bloodActiveNormal) {
			interPositivo = 5;
			interNegativo = -5;
		}
		//Si la vida de Elise esta igual o por debajo de 1/5 de la vida maxima los latidos van mas rápidos
		if (currentLife <= bloodActiveFast) {
			interPositivo = 10;
			interNegativo = -10;
		}
		if (player_->getComponent<Player>()->getInvincible() && pant) {
			//pantalla blanca
			SDL_SetRenderDrawColor(renderer_, COLOR(0xFFFFFFFF));
			SDL_RenderClear(renderer_);
			SDL_RenderPresent(renderer_);
			SDL_Delay(100);

			//pantalla roja
			SDL_SetRenderDrawColor(renderer_, COLOR(0xD50000FF));
			SDL_RenderClear(renderer_);
			SDL_RenderPresent(renderer_);
			SDL_Delay(100);

			pant = false;
			SDL_SetRenderDrawColor(renderer_, COLOR(0x00000000));
		}
		else if (!player_->getComponent<Player>()->getInvincible())
			pant = true;
		if (currentLife <= bloodActiveNormal) {
			if (time > actualTime_ + time_) {
				
				if (alpha_ > 70) {
					i_ = interNegativo;
				}
				else if (alpha_ < 10) {
					i_ = interPositivo;
				}
				alpha_ += i_;

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