#include "Key.h"

void Key::load(int numDoor, string keyName)
{
	doorId = numDoor;
	keyName_ = keyName;

	initialDescription_ = description;
}
