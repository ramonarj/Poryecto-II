#pragma once
#include "Component.h"
#include "Font.h"
#include <string>

class ItemContainer;
class Interactible : public Component
{
private:
	std::string message_;
	double textX_;
	double textY_;
	Font* font_;
	SDL_Color color_;

	bool display_;

	virtual void render(Entity* e, Uint32 time);
	void setMessage(std::string newMsg) { message_ = newMsg; };
	void setDisplaying(bool displaying) { display_ = displaying; };
	bool isDisplaying() { return display_; };

public:
	Interactible(std::string message = "XD", double textX = 0, double textY = 0);
	~Interactible() {};
	virtual void interact(Entity* e) = 0; // Metodo abstracto de la interaccion
};

