#pragma once
#include "Component.h"

class BloodManager : public Component
{
public:
	BloodManager();
	~BloodManager();
	virtual void render(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
private:
	bool bloodOn_;		//Para activar o desactivar el feedback de la pantalla
	bool pant = true;	//Regula cuando se pone los bordes de la pantalla rojos

	SDL_Rect destrect;	//Rectangulo de la pantalla

	Entity* player_ = nullptr;

	SDL_Renderer* renderer_;
	Texture* bloodText;			//Textura de sangre en borde de pantalla
	Uint8 alpha_;

	Uint32 actualTime_ = 0, time_ = 20;	//ritmo de los latidos de la pantalla

	int alphaCorto_ = 50, alphaLargo_ = 100;
	int i_ = 0;
};
