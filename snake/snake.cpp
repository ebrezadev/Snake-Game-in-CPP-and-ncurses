#include "snake.h"
#include <ncurses.h>
#include "timelib.h"

int snake_minimum_length;
int snake_maximum_length;
int snake_minimum_speed;
int snake_maximum_speed;

Snake::Snake()
{
	reset();

	snake_speed = snake_minimum_speed;
}

Snake::~Snake()
{
	body.clear();
}

// Clear the body vector, center the snake head on the field and add minimum body units
void Snake::reset()
{
	body.clear();

	int x_center = field_columns / 2;
	int y_center = field_rows / 2;

	Unit snake_unit;

	for (int i = 0; i < snake_minimum_length; i++)
	{
		snake_unit.coordinates.x = x_center - i;
		snake_unit.coordinates.y = y_center;

		if (i == 0)
			snake_unit.isHead = true;
		else
			snake_unit.isHead = false;

		body.push_back(snake_unit);
	}

	head_direction = Field::direction_t::RIGHT;
}

// Increase snake length by one unit at the tail
void Snake::increaseSnakeLength(Field *field)
{
	Unit snake_unit;

	// Based on the cell direction of the tail, create a new unit with the same direction
	switch (field->cell_direction[body[body.size() - 1].coordinates.y][body[body.size() - 1].coordinates.x])
	{
	case Field::direction_t::UP:
		snake_unit.coordinates.y = body[body.size() - 1].coordinates.y + 1;
		snake_unit.coordinates.x = body[body.size() - 1].coordinates.x;
		break;
	case Field::direction_t::DOWN:
		snake_unit.coordinates.y = body[body.size() - 1].coordinates.y - 1;
		snake_unit.coordinates.x = body[body.size() - 1].coordinates.x;
		break;
	case Field::direction_t::LEFT:
		snake_unit.coordinates.y = body[body.size() - 1].coordinates.y;
		snake_unit.coordinates.x = body[body.size() - 1].coordinates.x + 1;
		break;
	case Field::direction_t::RIGHT:
		snake_unit.coordinates.y = body[body.size() - 1].coordinates.y;
		snake_unit.coordinates.x = body[body.size() - 1].coordinates.x - 1;
		break;
	default:
		break;
	}

	snake_unit.isHead = false;

	body.push_back(snake_unit);

	field->cell_direction[body[body.size() - 1].coordinates.y][body[body.size() - 1].coordinates.x] = field->cell_direction[body[body.size() - 2].coordinates.y][body[body.size() - 2].coordinates.x];
}

// Print the snake to the screen
void Snake::printSnake()
{
	for (int unit_index = 0; unit_index < (int)body.size(); unit_index++)
	{
		if (body[unit_index].isHead == true)
			mvwaddch(stdscr, body[unit_index].coordinates.y + y_offset + 1, body[unit_index].coordinates.x + x_offset + 1, ACS_CKBOARD);
		else
			mvwaddch(stdscr, body[unit_index].coordinates.y + y_offset + 1, body[unit_index].coordinates.x + x_offset + 1, ACS_CKBOARD);
	}
}

// Move player by one unit based on movement speed. Return 'true' if movement is done
bool Snake::movePlayer(Field *field)
{
	static int64_t previous = 0;

	auto now = timelib::milliseconds();
	if ((now - previous) >= (1000 / snake_speed))
	{
		// first two 'if's check if the head is inside boundaries of the field which STOPS movement if not
		if (body[0].coordinates.x >= 0 && body[0].coordinates.x < field_columns)
			if (body[0].coordinates.y >= 0 && body[0].coordinates.y < field_rows)
				// Iterate over body units and move each unit one block based on each of the field block directions
				for (int unit_index = 0; unit_index < (int)body.size(); unit_index++)
				{
					switch (field->cell_direction[body[unit_index].coordinates.y][body[unit_index].coordinates.x])
					{
					case Field::direction_t::UP:
						body[unit_index].coordinates.y--;
						break;
					case Field::direction_t::DOWN:
						body[unit_index].coordinates.y++;
						break;
					case Field::direction_t::RIGHT:
						body[unit_index].coordinates.x++;
						break;
					case Field::direction_t::LEFT:
						body[unit_index].coordinates.x--;
						break;
					default:
						break;
					}
				}

		// Now change the field direction of the head block based on head direction
		Coordinates head_coordinates = headCoordinates();

		if(head_coordinates.y >= 0 && head_coordinates.x >= 0)
			field->cell_direction[head_coordinates.y][head_coordinates.x] = head_direction;
			
		previous = now;

		changeSpeed();

		// Returning true indicates that a movement has happened, and the snake is now open to accept the next input
		return true;
	}

	// Returning false indicates that no movement has happened
	return false;
}

// Checks if the direction key hit is valid based on the snake head current direction
bool Snake::validPress(Field::direction_t direction)
{
	if (((head_direction == Field::direction_t::RIGHT) || (head_direction == Field::direction_t::LEFT)) && ((direction == Field::direction_t::UP) || (direction == Field::direction_t::DOWN)))
	{
		return true;
	}
	else if (((head_direction == Field::direction_t::UP) || (head_direction == Field::direction_t::DOWN)) && ((direction == Field::direction_t::LEFT) || (direction == Field::direction_t::RIGHT)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Check the winning condition based on the snake length
bool Snake::winCheck()
{
	if (body.size() >= (unsigned)snake_maximum_length)
		return true;
	else
		return false;
}

// Returns the coordinates of the snake head
Coordinates Snake::headCoordinates()
{
	Coordinates head_coordinate;

	for (int unit_index = 0; unit_index < (int)body.size(); unit_index++)
	{
		if (body[unit_index].isHead == true)
		{
			head_coordinate = body[unit_index].coordinates;
		}
	}

	return head_coordinate;
}

// Returns 'true' if the snake head has hit its own body
bool Snake::collisionBody()
{
	Coordinates head_coordinates = headCoordinates();

	for (int unit_index = 0; unit_index < (int)body.size(); unit_index++)
	{
		if ((body[unit_index].isHead == false) && (body[unit_index].coordinates == head_coordinates))
		{
			return true;
		}
	}

	return false;
}

// Returns 'true' if the snake head has hit a wall
bool Snake::collisionWall()
{
	Coordinates head_coordinates = headCoordinates();

	if (head_coordinates.x >= 0 && head_coordinates.x < field_columns)
		if (head_coordinates.y >= 0 && head_coordinates.y < field_rows)
			return false;
	return true;
}

// Returns the current snake speed
int Snake::getSnakeSpeed()
{
	return snake_speed;
}

// Accepts a coordinate and returns 'true' if the coordinate matches a snake body unit's coordinate
bool Snake::isBodyCoordinate(Coordinates coordinate)
{
	for (int unit_index = 0; unit_index < (int)body.size(); unit_index++)
	{
		if (body[unit_index].coordinates == coordinate)
		{
			return true;
		}
	}

	return false;
}

// Returns the snake body length
int Snake::getSnakeLength()
{
	return body.size();
}

// Changes snake speed linearly based on the minimum/maximum length, minimum/maximum speed and current length
void Snake::changeSpeed()
{
	snake_speed = (int)(((float)(snake_maximum_speed - snake_minimum_speed) / (float)(snake_maximum_length - snake_minimum_length)) * (body.size() - snake_minimum_length) + (float)snake_minimum_speed);
}