#pragma once
#include "Interactible.h"



class Code : public Interactible
{
public:
	Code();
	~Code();

	virtual void interact(Entity* e);

	void load(int numDoor, int code);

	void setCodeActive(bool b) { codeActive_ = b; };
	bool getCodeActive() { return codeActive_; };

	void setAccept(bool b) { accept_ = b; };
	bool getAccept() { return accept_; };

	int getNumCode() { return code_; };

	int getNumDoorCode() { return numDoor_; };

private:
	int numDoor_;
	int code_;
	bool codeActive_;
	bool accept_;
};

