#ifndef __UNIT_H__
#define __UNIT_H__

#include "coordinates.h"

class Unit
{
public:
	Unit(){};
	~Unit(){};
	Coordinates coordinates;
	bool isHead;	
};

#endif