#include "SecurityCamera.h"



SecurityCamera::SecurityCamera() : Component(), numCamera_(0)
{
}


SecurityCamera::~SecurityCamera()
{
}

void SecurityCamera::load(int numCamera)
{
	numCamera_ = numCamera;
	cout << numCamera_;
}
