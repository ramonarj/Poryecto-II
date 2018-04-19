#pragma once
#include "Component.h"

class MessageRenderer :
	public Component
{
public:
	MessageRenderer();
	~MessageRenderer();
	void setDisplaying(bool displaying) { display_ = displaying; };
	void display(std::string message, double textX, double textY);
	bool isDisplaying() { return display_; };
	void setMessage(std::string newMsg) { message_ = newMsg; };
	void setPosition(double x, double y) { textX_ = x; textY_ = y; };

private:
	std::string message_;
	double textX_;
	double textY_;
	Font* font_;
	SDL_Color color_;
	bool display_;

	virtual void render(Entity* e, Uint32 time);
};