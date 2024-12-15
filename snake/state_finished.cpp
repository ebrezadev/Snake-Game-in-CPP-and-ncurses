#include "states.h"
#include <ncurses.h>
#include <cstring>
#include <alphabet_draw.h>

State_Finished::State_Finished()
{
	screen_update_flag = true;
}

State_Finished::state_return_t State_Finished::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Finished;

	getmaxyx(stdscr, max_rows, max_columns);

	if (screen_update_flag)
	{
		if (has_won)
		{
			erase();
			wattron(stdscr, A_DIM | A_BLINK | COLOR_PAIR(3));
			DrawString::drawString((char *)"YOU WIN!", (max_columns - (strlen((char *)"YOU WIN!") * 5) - strlen((char *)"YOU WIN!") + 1) / 2, 2);
			wattroff(stdscr, A_DIM | A_BLINK | COLOR_PAIR(3));
			wattron(stdscr, A_DIM);
			mvprintw(10, (max_columns - strlen((char *)"Press ENTER...")) / 2, "%s", (char *)"Press ENTER...");
			wattroff(stdscr, A_DIM);
		}
		else
		{
			erase();
			wattron(stdscr, A_DIM | A_BLINK | COLOR_PAIR(1));
			DrawString::drawString((char *)"YOU LOSE!", (max_columns - (strlen((char *)"YOU LOSE!") * 5) - strlen((char *)"YOU LOSE!") + 1) / 2, 2);
			wattroff(stdscr, A_DIM | A_BLINK | COLOR_PAIR(1));
			wattron(stdscr, A_DIM);
			mvprintw(10, (max_columns - strlen((char *)"Press ENTER...")) / 2, "%s", (char *)"Press ENTER...");
			wattroff(stdscr, A_DIM);
		}
	}

	switch (input)
	{
	case KEY_UP:
		screen_update_flag = false;
		break;
	case KEY_DOWN:
		screen_update_flag = false;
		break;
	case (int)13:
		next_state = State_list_t::State_Main_Menu;
		screen_update_flag = true;
		break;
	case KEY_LEFT:
		screen_update_flag = false;
		break;
	case KEY_RIGHT:
		screen_update_flag = false;
		break;
	case ' ':
		screen_update_flag = false;
		break;
	default:
		screen_update_flag = false;
		break;
	}

	return {next_state, screen_update_flag};
}
