#include "Interactible.h"

Interactible::Interactible(std::string interactMessage, bool msgIsName) : interactMessage_(interactMessage),
msgIsName_(msgIsName){
	
}

void Interactible::update(Entity * e, Uint32 time) {
	if (msgIsName_ && interactMessage_ == "") {
		interactMessage_ = e->getName();
		msgIsName_ = false;
	}
}
