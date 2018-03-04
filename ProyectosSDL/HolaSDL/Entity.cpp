#include "Entity.h"

Entity::~Entity() {
}

Entity::Entity(SDLGame* game) :
	game_(game), active_(true), width_(0), height_(0), position_(0, 0), direction_(1, 0), velocity_(0, 0), inputComp_(), logicComp_(), renderComp_() {
}

Entity::Entity(SDLGame* game, int posX, int posY) :
	game_(game), active_(true), width_(0), height_(0), position_(posX, posY), direction_(1, 0), velocity_(0, 0), inputComp_(), logicComp_(), renderComp_() {
}



void Entity::handleInput(Uint32 time, const SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		if (ic->isEnabled())
			ic->handleInput(this, time, event);
	}
}

void Entity::update(Uint32 time) {
	for (LogicComponent* lc : logicComp_) {
		if (lc->isEnabled())
			lc->update(this, time);
	}
}

void Entity::render(Uint32 time) {
	for (RenderComponent* rc : renderComp_) {
		if (rc->isEnabled())
			rc->render(this, time);
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

void Entity::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void Entity::addLogicComponent(LogicComponent* lc) {
	logicComp_.push_back(lc);
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

void Entity::delLogicComponent(LogicComponent* lc) {
	std::vector<LogicComponent*>::iterator position = std::find(
		logicComp_.begin(), logicComp_.end(), lc);
	if (position != logicComp_.end())
		logicComp_.erase(position);
}

void Entity::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}

////Heredados de GameObject

SDLGame* Entity::getGame() const {
	return game_;
}


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


