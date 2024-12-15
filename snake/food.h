/*
This file contains the class declaration of Food. Several methods need a pre-existing Snake object.
*/
#ifndef __FOOD_H__
#define __FOOD_H__

#include "snake_config.h"
#include "coordinates.h"
#include "snake.h"

class Food{
public:
	Food(Snake *snake);
	~Food();
	bool hitFood(Snake *snake);
	void showOrHideFood();
	void newFood(Snake *snake);

private:
	Coordinates coordinate;
};

#endif