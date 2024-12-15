/*
This file contains all the time-related functions of engine.
*/
#ifndef __TIMELIB_H__
#define __TIMELIB_H__

#include <iostream>

namespace timelib{
	int64_t milliseconds();
	void sleepMillis(int ms);
}

#endif