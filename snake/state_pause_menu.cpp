#include "states.h"
#include <ncurses.h>
#include <cstring>
#include <alphabet_draw.h>

State_Pause_Menu::State_Pause_Menu()
{
	screen_update_flag = true;
	current_menu = menu_t::CONTINUE;
}

State_Pause_Menu::state_return_t State_Pause_Menu::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Pause_Menu;

	if (screen_update_flag)
	{
		getmaxyx(stdscr, max_rows, max_columns);
		erase();
		attron(A_BOLD);
		mvprintw(3, (max_columns - strlen("GAME PAUSED")) / 2, "%s", "GAME PAUSED");
		attroff(A_BOLD);
		if (current_menu == menu_t::CONTINUE)
		{
			mvwaddch(stdscr, 5, ((max_columns - strlen("continue")) / 2) - 2, ACS_DIAMOND);
			mvprintw(5, (max_columns - strlen("continue")) / 2, "%s", "continue");
			attron(A_DIM);
			mvprintw(6, (max_columns - strlen("main menu")) / 2, "%s", "main menu");
			mvprintw(7, (max_columns - strlen("exit")) / 2, "%s", "exit");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::MAIN_MENU)
		{
			mvwaddch(stdscr, 6, ((max_columns - strlen("main menu")) / 2) - 2, ACS_DIAMOND);
			mvprintw(6, (max_columns - strlen("main menu")) / 2, "%s", "main menu");
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("continue")) / 2, "%s", "continue");
			mvprintw(7, (max_columns - strlen("exit")) / 2, "%s", "exit");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::EXIT)
		{
			mvwaddch(stdscr, 7, ((max_columns - strlen("exit")) / 2) - 2, ACS_DIAMOND);
			mvprintw(7, (max_columns - strlen("exit")) / 2, "%s", "exit");
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("continue")) / 2, "%s", "continue");
			mvprintw(6, (max_columns - strlen("main menu")) / 2, "%s", "main menu");
			attroff(A_DIM);
		}
	}

	switch (input)
	{
	case KEY_UP:
		current_menu = (menu_t)(((int)current_menu + 2) % 3);
		screen_update_flag = true;
		break;
	case KEY_DOWN:
		current_menu = (menu_t)(((int)current_menu + 1) % 3);
		screen_update_flag = true;
		break;
	case (int)13:
		if (current_menu == menu_t::CONTINUE)
		{
			next_state = State_list_t::State_Game;
		}
		else if (current_menu == menu_t::MAIN_MENU)
		{
			current_menu = menu_t::CONTINUE;
			next_state = State_list_t::State_Main_Menu;
		}
		else if (current_menu == menu_t::EXIT)
		{
			next_state = State_list_t::State_Exit;
		}
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
