#include "states.h"

State_Loading::State_Loading()
{
	screen_update_flag = true;
}

State_Loading::state_return_t State_Loading::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Loading;

	Game.reset();

	next_state = State_list_t::State_Game;

	return {next_state, screen_update_flag};
}
