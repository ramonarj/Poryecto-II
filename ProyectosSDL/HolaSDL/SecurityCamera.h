#pragma once
#include "Component.h"
class SecurityCamera : public Component
{
public:
	SecurityCamera();
	~SecurityCamera();

	void load(int numCamera);

private:
	int numCamera_;
};

