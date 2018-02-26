#pragma once
#include <vector>
#include <iostream>
#include "Vector2D.h"

using namespace std;

class Layer
{
public:

	virtual void render() = 0;
	virtual void update() = 0;

protected:

	virtual ~Layer() {}

};

