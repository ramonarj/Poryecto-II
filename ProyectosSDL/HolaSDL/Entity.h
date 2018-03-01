#ifndef ENTITY_H_
#define ENTITY_H_

#include "InputComponent.h"
#include "LogicComponent.h"
#include "RenderComponent.h"

#include "SDLGame.h"
#include "Vector2D.h"

#include <vector>

using namespace std;

class Entity{
public:
	Entity(SDLGame* game);
	virtual ~Entity();

	void setActive(bool enabled) { active_ = enabled; };
	bool isActive() { return active_; };

	SDLGame* getGame() const;

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addLogicComponent(LogicComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delLogicComponent(LogicComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

	//Getters y setters

	double getWidth() const;
	void setWidth(double width);
	double getHeight() const;
	void setHeight(double height);
	void scale(double s);


	const Vector2D& getPosition() const;
	void setPosition(const Vector2D &pos);

	const Vector2D& getVelocity() const;
	void setVelocity(const Vector2D &vel);

	const Vector2D& getDirection() const;
	void setDirection(const Vector2D &vel);

	//Nuevos
	template<typename T>
	T getComponent();

private:
    SDLGame* game_; // pointer to the game:
	bool active_;

	Vector2D position_; // position
	Vector2D direction_; // angle in degrees (0) is considered facing left
	Vector2D velocity_; // direction

	double width_;  // width
	double height_; // height

	vector<InputComponent*> inputComp_;
	vector<LogicComponent*> logicComp_;
	vector<RenderComponent*> renderComp_;
};

#endif /* ENTITY_H_ */