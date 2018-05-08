#pragma once
#include "Component.h"
class SecurityCamera : public Component
{
public:
	SecurityCamera();
	~SecurityCamera();

	void load(int numCamera);
	int getNumCamera() { return numCamera_; };

private:
	int numCamera_;
};

