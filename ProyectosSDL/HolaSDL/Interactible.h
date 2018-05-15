#pragma once
#include "Component.h"
#include "Font.h"
#include <string>
#include "Entity.h"

class ItemContainer;
class Interactible : public Component {
public:
	Interactible(std::string interactMessage = "", bool msgIsName = false);
	~Interactible() {};
	virtual bool interact(Entity* e) = 0; // Metodo "abstracto" de la interaccion
	std::string* getInteractMessage() { return &interactMessage_; };
	virtual void update(Entity* e, Uint32 time);

protected:
	std::string interactMessage_;
	bool msgIsName_;
};