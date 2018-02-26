#include "Entity.h"

Entity::Entity(SDLGame* game) :	GameObject(game), enabled_(true), inputComp_(), physicsComp_(), renderComp_() {
}

Entity::~Entity() {
}

void Entity::handleInput(Uint32 time, const SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		ic->handleInput(this, time, event);
	}
}

void Entity::update(Uint32 time) {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(this, time);
	}
}

void Entity::render(Uint32 time) {
	for (RenderComponent* rc : renderComp_) {
		rc->render(this, time);
	}
}

void Entity::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void Entity::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void Entity::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void Entity::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void Entity::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end())
		physicsComp_.erase(position);
}

void Entity::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}
