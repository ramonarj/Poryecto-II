#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() {
}

GameStateMachine::~GameStateMachine() {
}

void GameStateMachine::popState() { //Borra el top de la pila de states y hace pop
	if (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void GameStateMachine::changeState(GameState* state) { //Cambia el valor de changedState_
	changeState_ = state;
}

int GameStateMachine::size() { //Cambia el valor de changedState_
	return states.size();
}


bool GameStateMachine::changeStateTick() { //Hace pop del estado actual y mete el que está en changedState_. Se llama al final del buque principal
	if (changeState_ != nullptr) {
		if (!states.empty()) states.pop();
		states.push(changeState_);
		changeState_ = nullptr;
		return true;
	}
	return false;
}

bool GameStateMachine::pushStateTick() { //Mete el estado que hay en pushState_. Se llama al final del bucle principal
	if (pushState_ != nullptr) {
		states.push(pushState_);
		pushState_ = nullptr;
		return true;
	}
	return false;
}

void GameStateMachine::pushState(GameState* state) { //Cambia el valor de pushState_
	pushState_ = state;
}