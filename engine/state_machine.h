/*
This file contains class description of State Machine. 
The state machine runs the logic of the game and transitions between different states.

Platform/Game/IO independent.
*/
#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "state_list.h"

// The state machine runs the logic of the game and transitions between different states.
class StateMachine{
public:
	StateMachine();
	~StateMachine();

	typedef struct{
		bool is_running;
		bool update;
	}state_machine_return_t;
	
	state_machine_return_t run(int input);			// Accepts the input from engine and runs the state machine

private:
	State_list_t current_state;
};

#endif