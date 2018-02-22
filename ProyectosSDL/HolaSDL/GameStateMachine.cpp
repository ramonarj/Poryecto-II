#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(){
}

GameStateMachine::~GameStateMachine(){
}

void GameStateMachine::popState(){ //Borra el top de la pila de states y hace pop
	if (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void GameStateMachine::changeState(GameState* state){ //Hace pop del estado actual y mete el pasado por parametro
	if (!states.empty()) states.pop();
	states.push(state);
}