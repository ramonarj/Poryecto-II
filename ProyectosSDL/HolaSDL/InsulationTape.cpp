#include "InsulationTape.h"
#include "Weapon.h"

InsulationTape::~InsulationTape()
{
}

void InsulationTape::interact() {
}

void InsulationTape::useItem(Entity* e) {
	if (e->getComponent<Weapon>()) {
		e->getComponent<Weapon>()->repair();
		Item::useItem(e);
	}
}