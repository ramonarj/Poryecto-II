#pragma once
#include "Component.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "NumberKey.h"
#include "KeypadScreen.h"

class KeyPadController;

class KeypadComponent :
	public Component
{
	//tener en cuenta que cuando se han introducido 4 n�meros no pueden introducirse m�s
public:
	KeypadComponent(Texture* image, Entity* codeEntity, int password);
	~KeypadComponent();

	void moveMarkSlot(int a);
	void clickMark();

	void setCodeValid(bool b) { codeValid = b; };
	bool getCodeValid() { return codeValid; };

private:

	struct coord {
		int x;
		int y;
	};

	virtual void update(Entity* e, Uint32 time) ;//
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event); //controla las pulsaciones del rat�n -> llama a "clicked" de cada tecla
	virtual void render(Entity* e, Uint32 time);//pinta la carcasa 

	void clear(); //Borra los n�meros introducidos
	bool validate();//Valida los n�meros que se han introducido
	void addNumber(int n);
	void validCode();

	bool codeValid = false;

	Entity* codeEntity_;

	float edge_, space_;
	//vector <int> numSequence; //Guarda los n�meros introducidos -> puede ser un int
	string password_, sequence_;
	Texture* numpad_, * background_;
	SDL_Renderer* pRenderer=nullptr;
	ResourceManager* resource = nullptr;
	NumberKey keys[4][3];
	KeypadScreen screen;
	SDL_Rect dest;

	float h, w;

	coord markSlot = { 1, 1 };
	KeyPadController* pc = nullptr;
	void renderMark(SDL_Rect DestRect);
};