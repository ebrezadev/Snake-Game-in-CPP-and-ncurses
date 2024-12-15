#include "state_machine.h"
#include "states.h"

StateMachine::StateMachine()
{
	// Start from the top of the list of states
	current_state = (State_list_t)0;
}

StateMachine::~StateMachine()
{

}

StateMachine::state_machine_return_t StateMachine::run(int input)
{
	State::state_return_t state_return = states_table[(int)current_state]->stateFunction(input);

	current_state = state_return.next_state;

	if(current_state == State_list_t::State_Exit)
		return {false, state_return.update};
	else
		return {true, state_return.update};
}
