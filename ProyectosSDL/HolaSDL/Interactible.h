#pragma once
#include "Component.h"
#include "Font.h"
#include <string>

class ItemContainer;
class Interactible : public Component {
public:
	Interactible(std::string interactMessage = "");
	~Interactible() {};
	virtual void interact(Entity* e) {}; // Metodo abstracto de la interaccion
	std::string* getInteractMessage() { return &interactMessage_; };
protected:
	std::string interactMessage_;
};

