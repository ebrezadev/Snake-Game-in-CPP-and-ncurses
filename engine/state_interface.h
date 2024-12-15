/*
This file contains virtual class definition for State class.
All other state classes of a specific game are derived from State class.
Game states are used inside state machine to build up a specific game.

Platform/Game/IO independent.
*/
#ifndef __STATE_INTERFACE_H__
#define __STATE_INTERFACE_H__

#include "state_list.h"

// Virtual State class is the parent of all the derived states classes of a specific game
class State
{
public:
	State() {};
	~State() {};

	typedef struct 											// The return type of every state function. contains the next state in case of state transition
	{
		State_list_t next_state;
		bool update;
	} state_return_t;

	virtual state_return_t stateFunction(int input) = 0;	// The main functionality of every derived state

protected:
	bool screen_update_flag; 								// In order to check if the screen has changed
	int max_rows;											// Maximum possible number of rows in a terminal
	int max_columns;										// Maximum possible number of columns in a terminal
};

#endif