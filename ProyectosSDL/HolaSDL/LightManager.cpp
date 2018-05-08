#include "LightManager.h"
#include "Game.h"

LightManager::LightManager(): playerLight_(PlayerLight()), lightsOn_(true) {
	renderer_ = Game::Instance()->getRenderer(); //Renderer principal
}

LightManager::~LightManager(){
}

void LightManager::render(Entity * e, Uint32 time) {

	if (player_ == nullptr)
		player_ = Game::Instance()->getEntityWithComponent<Player>();

	if (lightsOn_) {
		SDL_Texture* target_texture = SDL_CreateTexture( //textura Target (Mezcla final de las luces)
			renderer_,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			Game::Instance()->getWindowWidth(),
			Game::Instance()->getWindowHeight()
		);

		SDL_Rect rect_;

		

		SDL_SetRenderTarget(renderer_, target_texture); //Se pone como target del renderer solo esa textura

		

		for (Light* l : lights) { //Se pinta sobre la textura target todas las luces

			rect_ = RECT( //Rect destino de cada luz
				l->getPos().getX() - Camera::Instance()->getPosition().getX(),
				l->getPos().getY() - Camera::Instance()->getPosition().getY(),
				l->getTexture()->getWidth(),
				l->getTexture()->getHeight()
			);

			SDL_RenderCopy(renderer_, l->getTexture()->getSdlTexture(), nullptr, &rect_);

		}
		

		playerLight_.render(e, time);

		SDL_SetRenderTarget(renderer_, nullptr); //El renderer ya no solo pinta en la textura target

		SDL_Rect destrect_ = RECT( //Rect de la textura target final
			0,
			0,
			Game::Instance()->getWindowWidth(),
			Game::Instance()->getWindowHeight()
		);

		SDL_SetTextureBlendMode(target_texture, SDL_BLENDMODE_MOD); //Se pone el blend mode de la textura final a multiplicar

		SDL_RenderCopy(renderer_, target_texture, &destrect_, &destrect_); //Se renderiza la textura final
		//SDL_RenderCopyEx(renderer_, target_texture, &destrect_, &destrect_, 0, 0, SDL_FLIP_NONE); //Se renderiza la textura final

		

		SDL_SetRenderTarget(renderer_, target_texture); //Se pone como target del renderer solo esa textura
		SDL_RenderClear(renderer_);
		SDL_SetRenderTarget(renderer_, nullptr); //El renderer ya no solo pinta en la textura target

		SDL_DestroyTexture(target_texture);
	}
}

void LightManager::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_l)
			lightsOn_ = !lightsOn_;
	}
}
