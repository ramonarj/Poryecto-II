#ifndef ENTITY_H_
#define ENTITY_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "LogicComponent.h"
#include "RenderComponent.h"

#include <vector>

using namespace std;

class Entity: public GameObject {
public:
	Entity(SDLGame* game);
	virtual ~Entity();

	void setEnabled(bool enabled) { enabled_ = enabled; };
	bool isEnabled() { return enabled_; };

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addLogicComponent(LogicComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delLogicComponent(LogicComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

	//Nuevos
	template<typename T>
	T getComponent();

private:
	bool enabled_;

	vector<InputComponent*> inputComp_;
	vector<LogicComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;
};

#endif /* ENTITY_H_ */