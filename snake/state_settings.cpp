#include "states.h"
#include <ncurses.h>
#include <cstring>

const int safe_min_rows = 10;
const int safe_min_columns = 10;
const int safe_snake_minimum_length = 1;
const int safe_snake_maximum_length = 1000;
const int safe_snake_minimum_speed = 1;
const int safe_snake_maximum_speed = 200;
const int min_FPS = 1;
const int max_FPS = 200;

State_Settings::State_Settings()
{
	screen_update_flag = true;
	current_menu = menu_t::BACK;
}

State::state_return_t State_Settings::stateFunction(int input)
{
	int safe_max_rows;
	int safe_max_columns;

	static int set_rows = DEFAULT_ROWS;
	static int set_columns = DEFAULT_COLUMNS;
	static int set_snake_minimum_length = DEFAULT_SNAKE_MINIMUM_LENGTH;
	static int set_snake_maximum_length = DEFAULT_SNAKE_MAXIMUM_LENGTH;
	static int set_snake_minimum_speed = DEFAULT_SNAKE_MINIMUM_SPEED;
	static int set_snake_maximum_speed = DEFAULT_SNAKE_MAXIMUM_SPEED;
	static int set_FPS = DEFAULT_FPS;

	getmaxyx(stdscr, max_rows, max_columns);

	safe_max_rows = max_rows - 5;
	safe_max_columns = max_columns - 4;

	State_list_t next_state = State_list_t::State_Settings;

	if (screen_update_flag)
	{
		getmaxyx(stdscr, max_rows, max_columns);
		erase();
		attron(A_BOLD);
		mvprintw(3, (max_columns - strlen("SETTINGS")) / 2, "%s", "SETTINGS");
		attroff(A_BOLD);

		if (current_menu == menu_t::ROWS_SETTING)
		{
			mvwaddch(stdscr, 5, ((max_columns - strlen("rows: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			attron(A_DIM);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			mvwaddch(stdscr, 6, ((max_columns - strlen("columns: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::SNAKE_MIN_LENGTH_SETTING)
		{
			mvwaddch(stdscr, 7, ((max_columns - strlen("snake minimum length: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::SNAKE_MAX_LENGTH_SETTING)
		{
			mvwaddch(stdscr, 8, ((max_columns - strlen("snake maximum length: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::SNAKE_MIN_SPEED_SETTING)
		{
			mvwaddch(stdscr, 9, ((max_columns - strlen("snake minimum speed: ") - 14) / 2) - 2, ACS_DIAMOND);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::SNAKE_MAX_SPEED_SETTING)
		{
			mvwaddch(stdscr, 10, ((max_columns - strlen("snake maximum speed: ") - 14) / 2) - 2, ACS_DIAMOND);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::BACK)
		{
			mvwaddch(stdscr, 11, ((max_columns - strlen("back")) / 2) - 2, ACS_DIAMOND);
			mvprintw(11, (max_columns - strlen("back")) / 2, "%s", "back");
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("snake minimum length: ") - 3) / 2, "snake minimum length: %d", set_snake_minimum_length);
			mvprintw(8, (max_columns - strlen("snake maximum length: ") - 3) / 2, "snake maximum length: %d", set_snake_maximum_length);
			mvprintw(9, (max_columns - strlen("snake minimum speed: ") - 14) / 2, "snake minimum speed: %d blocks/sec", set_snake_minimum_speed);
			mvprintw(10, (max_columns - strlen("snake maximum speed: ") - 14) / 2, "snake maximum speed: %d blocks/sec", set_snake_maximum_speed);
			attroff(A_DIM);
		}

		attron(A_ITALIC | A_DIM);
		mvprintw(14, (max_columns - strlen("UP/DOWN to choose")) / 2, "UP/DOWN to choose");
		mvprintw(15, (max_columns - strlen("LEFT/RIGHT to change")) / 2, "LEFT/RIGHT to change");
		mvprintw(16, (max_columns - strlen("SPACE to set defaults")) / 2, "SPACE to set defaults");
		attroff(A_ITALIC | A_DIM);
	}

	switch (input)
	{
	case KEY_UP:
		current_menu = (menu_t)(((int)current_menu + 6) % 7);
		screen_update_flag = true;
		break;
	case KEY_DOWN:
		current_menu = (menu_t)(((int)current_menu + 1) % 7);
		screen_update_flag = true;
		break;
	case (int)13:
		if (current_menu == menu_t::BACK)
		{
			field_rows = set_rows;
			field_columns = set_columns;
			snake_minimum_length = set_snake_minimum_length;
			snake_maximum_length = set_snake_maximum_length;
			snake_minimum_speed = set_snake_minimum_speed;
			snake_maximum_speed = set_snake_maximum_speed;
			FPS = set_FPS;
			period_ms = 1000 / FPS;
			input_timeout_ms = (period_ms * 3) / 4;
			sleep_ms = period_ms / 5;
			next_state = State_list_t::State_Main_Menu;
			screen_update_flag = true;
		}
		else
			screen_update_flag = false;
		break;
	case KEY_LEFT:
		if (current_menu == menu_t::ROWS_SETTING)
		{
			if (set_rows > safe_min_rows)
				set_rows -= 1;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			if (set_columns > safe_min_columns)
			{
				if (set_snake_minimum_length >= (set_columns / 2))
					set_snake_minimum_length--;
				set_columns--;
			}
		}
		else if (current_menu == menu_t::SNAKE_MIN_LENGTH_SETTING)
		{
			if (set_snake_minimum_length > safe_snake_minimum_length)
				set_snake_minimum_length--;
		}
		else if (current_menu == menu_t::SNAKE_MAX_LENGTH_SETTING)
		{
			if (set_snake_maximum_length > (set_snake_minimum_length + 1))
				set_snake_maximum_length--;
		}
		else if (current_menu == menu_t::SNAKE_MIN_SPEED_SETTING)
		{
			if (set_snake_minimum_speed > safe_snake_minimum_speed)
				set_snake_minimum_speed--;
		}
		else if (current_menu == menu_t::SNAKE_MAX_SPEED_SETTING)
		{
			if (set_snake_maximum_speed > set_snake_minimum_speed)
				set_snake_maximum_speed--;
		}
		screen_update_flag = true;
		break;
	case KEY_RIGHT:
		if (current_menu == menu_t::ROWS_SETTING)
		{
			if (set_rows < safe_max_rows && set_rows < MAX_FIELD_ROWS)
				set_rows += 1;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			if (set_columns < safe_max_columns && set_columns < MAX_FIELD_COLUMNS)
				set_columns += 1;
		}
		else if (current_menu == menu_t::SNAKE_MIN_LENGTH_SETTING)
		{
			if ((set_snake_minimum_length < (set_snake_maximum_length - 1)) && (set_snake_minimum_length <= (set_columns / 2)))
				set_snake_minimum_length++;
		}
		else if (current_menu == menu_t::SNAKE_MAX_LENGTH_SETTING)
		{
			if (set_snake_maximum_length < safe_snake_maximum_length)
				set_snake_maximum_length++;
		}
		else if (current_menu == menu_t::SNAKE_MIN_SPEED_SETTING)
		{
			if (set_snake_minimum_speed < set_snake_maximum_speed)
				set_snake_minimum_speed++;
		}
		else if (current_menu == menu_t::SNAKE_MAX_SPEED_SETTING)
		{
			if (set_snake_maximum_speed < safe_snake_maximum_speed)
				set_snake_maximum_speed++;
		}
		screen_update_flag = true;
		break;
	case ' ':
		if (current_menu == menu_t::ROWS_SETTING)
		{
			set_rows = DEFAULT_ROWS;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			set_columns = DEFAULT_COLUMNS;
		}
		else if (current_menu == menu_t::SNAKE_MIN_LENGTH_SETTING)
		{
			set_snake_minimum_length = DEFAULT_SNAKE_MINIMUM_LENGTH;
		}
		else if (current_menu == menu_t::SNAKE_MAX_LENGTH_SETTING)
		{
			set_snake_maximum_length = DEFAULT_SNAKE_MAXIMUM_LENGTH;
		}
		else if (current_menu == menu_t::SNAKE_MIN_SPEED_SETTING)
		{
			set_snake_minimum_speed = DEFAULT_SNAKE_MINIMUM_SPEED;
		}
		else if (current_menu == menu_t::SNAKE_MAX_SPEED_SETTING)
		{
			set_snake_maximum_speed = DEFAULT_SNAKE_MAXIMUM_SPEED;
		}
		screen_update_flag = true;
		break;
	default:
		screen_update_flag = false;
		break;
	}

	if (set_rows > safe_max_rows)
	{
		set_rows = safe_max_rows;
		screen_update_flag = true;
	}
	if (set_columns > safe_max_columns)
	{
		set_columns = safe_max_columns;
		screen_update_flag = true;
	}

	return {next_state, screen_update_flag};
}