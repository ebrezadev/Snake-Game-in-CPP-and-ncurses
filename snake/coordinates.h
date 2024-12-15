/*
This file contains the Coordinates class declaration and definition, used by other classes.
*/
#ifndef __COORDINATES_H__
#define __COORDINATES_H__

class Coordinates
{
public:
	Coordinates() {};
	~Coordinates() {};

	int x;
	int y;

	bool operator==(const Coordinates &coordinates)
	{
		if (coordinates.x == x && coordinates.y == y)
			return true;
		else
			return false;
	};
};

#endif