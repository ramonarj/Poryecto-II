#pragma once
#include "Component.h"
#include "Font.h"
#include <string>

class ItemContainer;
class Interactible : public Component {
public:
	Interactible(std::string interactMessage = "");
	~Interactible() {};
	virtual void interact(Entity* e) = 0; // Metodo abstracto de la interaccion
	std::string* getInteractMessage() { return &interactMessage_; };
private:
	std::string interactMessage_;
};

