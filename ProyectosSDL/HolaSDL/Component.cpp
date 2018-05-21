#include "Component.h"
#include "Entity.h"
#include <cmath>
#include <algorithm>

Component::Component(): enabled_(true), deltaTime(0.0), lastTime(0.0) {
}


Component::~Component() {
}

void Component::timing(Uint32 time) {
	deltaTime = time - lastTime;
	lastTime = time;
	deltaTime = deltaTime / 10;
	if (deltaTime > 100) deltaTime = 100;
}
