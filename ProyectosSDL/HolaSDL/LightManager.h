#pragma once
#include "Component.h"
#include "Light.h"
#include "PlayerLight.h"

class LightManager : public Component {
public:
	LightManager();
	~LightManager();
	virtual void render(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);
	void addLight(Light* light) { lights.push_back(light); };

private:
	bool lightsOn_;
	SDL_Texture* target_texture;
	SDL_Renderer* renderer_;
	vector<Light*> lights;
	PlayerLight playerLight_;
};

