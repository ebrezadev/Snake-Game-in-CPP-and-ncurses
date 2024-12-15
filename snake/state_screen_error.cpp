#include "states.h"
#include <ncurses.h>
#include <cstring>

State_Screen_Error::State_Screen_Error()
{
	screen_update_flag = true;
}

State_Screen_Error::state_return_t State_Screen_Error::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Screen_Error;

	getmaxyx(stdscr, max_rows, max_columns);

	if(screen_update_flag)
	{
		clear();
		mvprintw(0, (max_columns - strlen("PLEASE EXPAND SCREEN")) / 2, "%s", "PLEASE EXPAND SCREEN");
	}
	
	screen_update_flag = false;

	if (!(max_rows < MINIMUM_ROWS || max_columns < MINIMUM_COLUMNS))
	{
		next_state = State_list_t::State_Main_Menu;
		screen_update_flag = true;
	}

	return {next_state, screen_update_flag};
}
