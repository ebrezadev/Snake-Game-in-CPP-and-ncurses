#include "states.h"
#include <ncurses.h>
#include <cstring>
#include <alphabet_draw.h>

State_Main_Menu::State_Main_Menu()
{
	screen_update_flag = true;
	current_menu = menu_t::START_GAME;
}

State_Main_Menu::state_return_t State_Main_Menu::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Main_Menu;

	getmaxyx(stdscr, max_rows, max_columns);
	
	x_offset = (max_columns - field_columns) / 2;
	y_offset = (max_rows - field_rows) / 2;

	if (screen_update_flag)
	{
		erase();
		attron(A_BOLD | COLOR_PAIR(3));
		DrawString::drawString((char *)"SNAKE", (max_columns - strlen((char *)"SNAKE") * 5 - strlen((char *)"SNAKE") + 1) / 2, 2);
		attroff(A_BOLD | COLOR_PAIR(3));

		if (current_menu == menu_t::START_GAME)
		{
			mvwaddch(stdscr, 9, ((max_columns - strlen((char *)"START GAME")) / 2) - 2, ACS_DIAMOND);
			mvprintw(9, (max_columns - strlen((char *)"START GAME")) / 2, "%s", (char *)"START GAME");
			attron(A_DIM);
			mvprintw(10, (max_columns - strlen((char *)"SETTINGS")) / 2, "%s", (char *)"SETTINGS");
			mvprintw(11, (max_columns - strlen((char *)"EXIT")) / 2, "%s", (char *)"EXIT");
			attroff(A_DIM);
		}
		else if(current_menu == menu_t::SETTINGS)
		{
			mvwaddch(stdscr, 10, ((max_columns - strlen((char *)"SETTINGS")) / 2) - 2, ACS_DIAMOND);
			mvprintw(10, (max_columns - strlen((char *)"SETTINGS")) / 2, "%s", (char *)"SETTINGS");
			attron(A_DIM);
			mvprintw(9, (max_columns - strlen((char *)"START GAME")) / 2, "%s", (char *)"START GAME");
			mvprintw(11, (max_columns - strlen((char *)"EXIT")) / 2, "%s", (char *)"EXIT");
			attroff(A_DIM);
		}
		else if(current_menu == menu_t::EXIT)
		{
			mvwaddch(stdscr, 11, ((max_columns - strlen((char *)"EXIT")) / 2) - 2, ACS_DIAMOND);
			mvprintw(11, (max_columns - strlen((char *)"EXIT")) / 2, "%s", (char *)"EXIT");
			attron(A_DIM);
			mvprintw(9, (max_columns - strlen((char *)"START GAME")) / 2, "%s", (char *)"START GAME");
			mvprintw(10, (max_columns - strlen((char *)"SETTINGS")) / 2, "%s", (char *)"SETTINGS");
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
	case (int)13: // ENTER
		if (current_menu == menu_t::START_GAME)
		{
			next_state = State_list_t::State_Loading;
		}
		else if(current_menu == menu_t::SETTINGS)
		{
			next_state = State_list_t::State_Settings;
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

	if (max_rows < MINIMUM_ROWS || max_columns < MINIMUM_COLUMNS)
	{
		next_state = State_list_t::State_Screen_Error;
		screen_update_flag = true;
	}

	return {next_state, screen_update_flag};
}
