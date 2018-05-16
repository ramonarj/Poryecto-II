#include "Key.h"

void Key::load(int numDoor, string keyName)
{
	doorId = numDoor;
	keyName_ = keyName;

	initialDescription_ = description;

	description = initialDescription_ + "\n" + keyName_ + "\n";
}
