#pragma once
#include "Component.h"
#include "Light.h"
#include "PlayerLight.h"
#include "checkML.h"


class LightManager : public Component {
public:
	LightManager();
	~LightManager();
	virtual void render(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	void addLight(Light* light) { lights.push_back(light); };

private:
	bool lightsOn_;
	
	Entity* player_=nullptr;

	SDL_Renderer* renderer_;
	vector<Light*> lights;
	PlayerLight playerLight_;
};

