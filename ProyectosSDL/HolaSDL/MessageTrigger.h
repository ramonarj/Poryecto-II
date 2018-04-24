#pragma once
#include "Component.h"
#include "MessageRenderer.h"
#include "ControllerInputComponent.h"

class MessageTrigger : public Component {
public:
	MessageTrigger(std::string message); // Independiente del tipo de control del juego
	MessageTrigger(std::string KBmessage, std::string CNTmessage); // Dos mensajes: Teclado y Controller
	~MessageTrigger();
	virtual void update(Entity* e, Uint32 time);
	void setMessage(std::string message, bool displayNow = false);
	void setMessage(std::string KBmessage, std::string CNTmessage, bool displayNow = true);

private:
	std::string KBmessage_;
	std::string CNTmessage_;
	bool last;

	MessageRenderer* messageRenderer;
	Entity* player;
	ControllerInputComponent* CNTcomp;

	SDL_Rect thisRect;
};

