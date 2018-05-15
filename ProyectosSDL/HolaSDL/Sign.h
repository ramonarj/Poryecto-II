#pragma once
#include "Interactible.h"
#include "TextNote.h"
#include "MessageTrigger.h"

class Sign : public Interactible
{
public:
	Sign();
	~Sign();

	void load(Entity* e, int numSign, std::string ori);
	virtual bool interact(Entity* e);
	bool canLookSign();
	virtual void update(Entity* e, Uint32 time);

private:

	TextNote * textNote_;
	MessageTrigger * messageTrigger_;
	std::string KBmessage_;
	std::string CNTmessage_;
	Uint32 time_;

	std::string ori_;

	bool sign_;
	Uint32 signOn_;
	Uint32 signTime_;
};

