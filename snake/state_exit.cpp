#include "states.h"

State_Exit::State_Exit()
{
}

State_Exit::state_return_t State_Exit::stateFunction(int input)
{
	return {State_list_t::State_Exit, true};
}
