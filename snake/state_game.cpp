#include "states.h"
#include <ncurses.h>
#include <cstring>
#include <alphabet_draw.h>

constexpr int INPUT_FIFO_BUFFER_DEPTH = 5;

State_Game::State_Game()
{
	screen_update_flag = true;
	field = nullptr;
	snake = nullptr;
	food = nullptr;
	field_columns = DEFAULT_COLUMNS;
	field_rows = DEFAULT_ROWS;
	snake_minimum_length = DEFAULT_SNAKE_MINIMUM_LENGTH;
	snake_maximum_length = DEFAULT_SNAKE_MAXIMUM_LENGTH;
	snake_minimum_speed = DEFAULT_SNAKE_MINIMUM_SPEED;
	snake_maximum_speed = DEFAULT_SNAKE_MAXIMUM_SPEED;
}

State_Game::state_return_t State_Game::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Game;

	Coordinates head_coordinates = snake->headCoordinates();

	getmaxyx(stdscr, max_rows, max_columns);

	switch (input)
	{
	case KEY_UP:
	case KEY_DOWN:
	case KEY_RIGHT:
	case KEY_LEFT:
		// Push to FIFO with a pre-determined buffer depth
		if (input_fifo.size() < INPUT_FIFO_BUFFER_DEPTH)
			input_fifo.push(input);
		break;
	case (int)13:
		break;
	case ' ':
		next_state = State_list_t::State_Pause_Menu;
		screen_update_flag = true;
		break;
	default:
		break;
	}

	// Check the FIFO buffer for the first input
	switch (input_fifo.front())
	{
	case KEY_UP:
		if (snake->validPress(Field::direction_t::UP))
		{
			snake->head_direction = Field::direction_t::UP;
			field->cell_direction[head_coordinates.y][head_coordinates.x] = Field::direction_t::UP;
		}
		break;
	case KEY_DOWN:
		if (snake->validPress(Field::direction_t::DOWN))
		{
			snake->head_direction = Field::direction_t::DOWN;
			field->cell_direction[head_coordinates.y][head_coordinates.x] = Field::direction_t::DOWN;
		}
		break;
	case KEY_RIGHT:
		if (snake->validPress(Field::direction_t::RIGHT))
		{
			snake->head_direction = Field::direction_t::RIGHT;
			field->cell_direction[head_coordinates.y][head_coordinates.x] = Field::direction_t::RIGHT;
		}
		break;
	case KEY_LEFT:
		if (snake->validPress(Field::direction_t::LEFT))
		{
			snake->head_direction = Field::direction_t::LEFT;
			field->cell_direction[head_coordinates.y][head_coordinates.x] = Field::direction_t::LEFT;
		}
		break;
	default:
		break;
	}

	// Call the movePlayer method. If a movement is done, pop an element from FIFO buffer.
	if (snake->movePlayer(field))
	{
		screen_update_flag = true;

		if (!input_fifo.empty())
		{
			input_fifo.pop();
		}
	}
	else
	{
		screen_update_flag = false;
	}

	// Check collision conditions, then winning condition, then food hit condition
	if (snake->collisionBody() || snake->collisionWall())
	{
		Finished.has_won = false;
		next_state = State_list_t::State_Finished;
	}
	else if (snake->winCheck())
	{
		Finished.has_won = true;
		next_state = State_list_t::State_Finished;
	}
	else if (food->hitFood(snake))
	{
		snake->increaseSnakeLength(field);
		food->newFood(snake);
	}

	// Print everything to the screen
	werase(stdscr);

	int snake_length = snake->getSnakeLength();
	int snake_speed = snake->getSnakeSpeed();

	mvwprintw(stdscr, y_offset - 1, (max_columns - strlen("SCORE:   SPEED:   blocks/sec") - 2) / 2, "SCORE: %d   SPEED: %d blocks/sec", snake_length, snake_speed);
	mvwprintw(stdscr, y_offset + 2 + field_rows, (max_columns - strlen("SPACE to pause")) / 2, "SPACE to pause");
	field->printWalls();

	attron(COLOR_PAIR(2));
	snake->printSnake();
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(1));
	food->showOrHideFood();
	attroff(COLOR_PAIR(1));

	return {next_state, screen_update_flag};
}

void State_Game::reset()
{
	if (field != nullptr)
		delete field;
	field = new Field;

	if (snake != nullptr)
		delete snake;
	snake = new Snake;

	if (food != nullptr)
		delete food;
	food = new Food(snake);

	screen_update_flag = true;
}
