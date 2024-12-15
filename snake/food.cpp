#include "food.h"
#include <iostream>
#include <ncurses.h>
#include "timelib.h"

Food::Food(Snake *snake)
{
	// Seed the random generator once
	std::srand(time(0));

	newFood(snake);
}

Food::~Food()
{
}

// Prints the blinking food on the screen
void Food::showOrHideFood()
{
	attron(A_BLINK);
	mvwaddch(stdscr, y_offset + coordinate.y + 1, x_offset + coordinate.x + 1, ACS_DIAMOND);
	attroff(A_BLINK);
}

// Randomly positions new food on the field. Avoids positioning on the snake body.
void Food::newFood(Snake *snake)
{
	for (;;)
	{
		coordinate.x = std::rand() % field_columns;
		coordinate.y = std::rand() % field_rows;

		if (snake->isBodyCoordinate(coordinate))
			continue;
		else
			break;
	}
}

// Checks if the snake head has hit the food.
bool Food::hitFood(Snake *snake)
{
	Coordinates head_coordinate = snake->headCoordinates();

	if (head_coordinate == coordinate)
	{
		return true;
	}

	return false;
}