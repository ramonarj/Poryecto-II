#pragma once
#include "Component.h"
#include "checkML.h"


class MessageRenderer :
	public Component
{
public:
	MessageRenderer();
	~MessageRenderer();
	void setDisplaying(bool displaying) { display_ = displaying; };
	void display(std::string message, double textX, double textY); // Se puede elegir donde se pinta el mensaje
	void display(std::string message); // Se pinta el mensaje en la posicion predeterminada
	bool isDisplaying() { return display_; };
	void setMessage(std::string newMsg) { message_ = newMsg; };
	void setPosition(double x, double y) { textX_ = x; textY_ = y; };
	void setFont(Font* f) { font_ = f; };
	void setColor(SDL_Color c) { color_ = c; };

private:
	std::string message_;
	double textX_;
	double textY_;
	Font* font_;
	SDL_Color color_;
	bool display_;

	virtual void render(Entity* e, Uint32 time);
};