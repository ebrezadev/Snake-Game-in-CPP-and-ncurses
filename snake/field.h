/*
This class contains everything related to field; thats printing outer walls and the direction of each cell
*/
#ifndef __FIELD_H__
#define __FIELD_H__

#include "snake_config.h"

class Field{
public:
	Field();
	~Field(){};
	void printWalls();

	enum class direction_t{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	direction_t cell_direction[MAX_FIELD_ROWS][MAX_FIELD_COLUMNS];
};

#endif