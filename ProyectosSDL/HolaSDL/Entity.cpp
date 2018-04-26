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
	for (int i = 0; i < 4; i++)
		sideCollision.push_back(false);
}

Entity::Entity(int posX, int posY) :
	active_(true), width_(0), height_(0), position_(posX, posY), direction_(1, 0), velocity_(0, 0), comps_() {
}



void Entity::handleInput(Uint32 time, const SDL_Event& event) {
	if (isActive()) {
		for (Component* c : comps_) {
			if (c->isEnabled())
				c->handleInput(this, time, event);
		}
	}
}

void Entity::update(Uint32 time) {
	if (isActive()) {
		for (Component* c : comps_) {
			if (c->isEnabled())
				c->update(this, time);
		}
	}
}

void Entity::render(Uint32 time) {
	if (isActive()) {
		for (Component* c : comps_) {
			if (c->isEnabled())
				c->render(this, time);
		}
	}
}

void Entity::saveToFile()
{
	if (isActive()) {
		for (Component* c : comps_) {
			if (c->isEnabled())
				c->saveToFile(this);
		}
	}
}

void Entity::loadToFile()
{
	if (isActive()) {
		for (Component* c : comps_) {
			if (c->isEnabled())
				c->loadToFile(this);
		}
	}
}

void Entity::saveEntity(Entity* o, ofstream & file)
{
	file << o->isActive() << endl;
	file << o->getPosition().getX() << " " << o->getPosition().getY() << endl;
}

void Entity::loadEntity(Entity * o, ifstream & file)
{
	bool active;
	string s;

	file >> active;
	o->setActive(active);
	//Pasamos de línea
	getline(file, s);

	Vector2D v;
	double n;
	file >> n; v.setX(n); file >> n; v.setY(n); o->setPosition(v);
	//Pasamos de línea
	getline(file, s);
}

void Entity::load(int x, int y, int width, int height, int staticEntity, string name)
{
	position_.set(Vector2D(x, y));
	width_ = width;
	height_ = height;
	currentRow_ = 1;
	currentFrame_ = 1;

	staticEntity_ = staticEntity;

	name_ = name;
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

bool Entity::isStatic()
{
	return staticEntity_;
}

string Entity::getName()
{
	return name_;
}

bool Entity::getIsReading()
{
	return reading_;
}

void Entity::setIsReading(bool b)
{
	reading_ = b;
}

SDL_Rect Entity::getRect()
{
	SDL_Rect dest
	{ position_.getX(), position_.getY(), width_, height_ };

	return dest;
}

void Entity::setDirection(const Vector2D &vel) {
	direction_.set(vel);
	direction_.normalize();
}

void Entity::setSideCollision(int i)
{
	for (int j = 0; j < sideCollision.size(); j++)
	{
		if (i != j) sideCollision[j] = false;
		else sideCollision[j] = true;

		for (int i = 0; i < sideCollision.size(); i++) {

			if (sideCollision[i]) {
				if (i == 0) {
					std::cout << to_string(i) << std::endl;
				}
			}

		}
	}
}



