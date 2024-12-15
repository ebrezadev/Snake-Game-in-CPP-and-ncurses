/*
This file contains the class declaration of Snake, which is a vector of Unit objects.
*/
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include "field.h"
#include "unit.h"
#include "snake_config.h"

class Snake
{
public:
	Snake();
	~Snake();

	Field::direction_t head_direction;
	bool validPress(Field::direction_t direction);
	bool winCheck();
	bool collisionBody();
	bool collisionWall();
	bool isBodyCoordinate(Coordinates coordinate);
	int getSnakeSpeed();
	int getSnakeLength();
	bool movePlayer(Field *field);
	void increaseSnakeLength(Field *field);
	Coordinates headCoordinates();
	void printSnake();
	void changeSpeed();
	void reset();

private:
	std::vector<Unit> body;
	int snake_speed;
	
};

#endif