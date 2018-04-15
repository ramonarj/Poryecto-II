#ifndef ENTITY_H_
#define ENTITY_H_

#include "checkML.h"
#include "Component.h"
#include "SDLGame.h"
#include "Vector2D.h"

#include <vector>

using namespace std;

class Entity{
public:
	Entity();
	Entity(int posX, int posY);
	virtual ~Entity();

	void setActive(bool enabled);
	bool isActive() { return active_; };

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void load(int x, int y, int width, int height, int staticEntity);

	virtual void addComponent(Component* c);
	virtual void delComponent(Component* c);


	//Getters y setters

	double getWidth() const;
	void setWidth(double width);
	double getHeight() const;
	void setHeight(double height);
	void scale(double s);
	bool isStatic();

	SDL_Rect getRect();

	const Vector2D& getPosition() const;
	void setPosition(const Vector2D &pos);

	const Vector2D& getVelocity() const;
	void setVelocity(const Vector2D &vel);

	const Vector2D& getDirection() const;
	void setDirection(const Vector2D &vel);

	void setSideCollision(int i);


	//Get Component
	template<typename T>
	T* getComponent()
	{
		//Compopnent
		for (Component* c : comps_) {
			T* component = dynamic_cast<T*>(c);
			if (component != nullptr)
				return component;
		}

		//If component not found
		return nullptr;
	};

private:
	bool active_;

	Vector2D position_; // position
	Vector2D direction_; // angle in degrees (0) is considered facing left
	Vector2D velocity_; // direction

	double width_;  // width
	double height_; // height

	double currentRow_;
	double currentFrame_;

	vector<Component*> comps_;
	vector<bool> sideCollision;

	bool staticEntity_;
};

#endif /* ENTITY_H_ */
