#include "Entity.h"
#include "Camera.h"

Entity::~Entity() {
}

void Entity::setActive(bool enabled)
{
	active_ = enabled;
	for (Component* c : comps_) {
		c->setEnabled(enabled);
	}
}

Entity::Entity() :
	active_(true), width_(0), height_(0), position_(0, 0), direction_(1, 0), velocity_(0, 0), comps_() {
}

Entity::Entity(int posX, int posY) :
	active_(true), width_(0), height_(0), position_(posX, posY), direction_(1, 0), velocity_(0, 0), comps_() {
}



void Entity::handleInput(Uint32 time, const SDL_Event& event) {
	for (Component* c : comps_) {
		if (c->isEnabled())
			c->handleInput(this, time, event);
	}
}

void Entity::update(Uint32 time) {
	for (Component* c : comps_) {
		if (c->isEnabled())
			c->update(this, time);
	}
}

void Entity::render(Uint32 time) {
	for (Component* c : comps_) {
		if (c->isEnabled())
			c->render(this, time);
	}
}

void Entity::load(int x, int y, int width, int height, string textureID)
{
	position_ = Vector2D(x, y);
	width_ = width;
	height_ = height;
	textureID_ = textureID;
	currentRow_ = 1;
	currentFrame_ = 1;
}

void Entity::addComponent(Component* c) {
	comps_.push_back(c);
}

void Entity::delComponent(Component* c) {
	std::vector<Component*>::iterator position = std::find(
		comps_.begin(), comps_.end(), c);
	if (position != comps_.end())
		comps_.erase(position);
}


////Heredados de GameObject

double Entity::getWidth() const {
	return width_;
}

void Entity::setWidth(double width) {
	width_ = width;
}

double Entity::getHeight() const {
	return height_;
}

void Entity::setHeight(double height) {
	height_ = height;
}

const Vector2D& Entity::getPosition() const {
	return position_;
}

void Entity::setPosition(const Vector2D &pos) {
	position_.set(pos);
}

const Vector2D& Entity::getVelocity() const {
	return velocity_;
}

void Entity::setVelocity(const Vector2D &vel) {
	velocity_.set(vel);
}

const Vector2D& Entity::getDirection() const {
	return direction_;
}

void Entity::scale(double s) {
	width_ *= s;
	height_ *= s;
}

void Entity::setDirection(const Vector2D &vel) {
	direction_.set(vel);
	direction_.normalize();
}



