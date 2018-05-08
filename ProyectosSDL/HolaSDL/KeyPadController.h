#pragma once
#include "BaseControllerInput.h"
#include "KeypadComponent.h"
 

 
class KeyPadController :
  public BaseControllerInput
{
public:
  KeyPadController();
  virtual ~KeyPadController();
  virtual void handleInput(Entity* o, Uint32 time, const SDL_Event& event);
private:
  bool joystickMoved = true;
  int slot = 0;
  KeypadComponent* puzll_ = nullptr;
 
};
 