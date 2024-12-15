/*
This file contains the class description of IO.
IO is responsible for handling user input and passing it to the engine;
also responsible for refreshing the screen.
This class is depdendent on the TUI (Terminal User Interface) library.
*/
#ifndef __IO_H__
#define __IO_H__

class IO
{
public:
	static class IO *getInstance();
	IO(IO &other) = delete;
	void operator=(const IO &) = delete;
	void render();
	int input(int timeout);
	friend class Engine;

private:
	IO();
	~IO();
};

#endif