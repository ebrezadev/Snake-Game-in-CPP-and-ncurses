#include <ncurses.h>
#include "io.h"

WINDOW* input_window;

IO *IO::getInstance()
{
	static IO Instance;

	return &Instance;
}

IO::IO()
{
	/* Start curses mode and data structures for stdscr*/
	initscr();

	//input_window = newwin(1000,1000,0,0);

	/* Line buffering disabled, Pass on everything to me; except for 'ctrl + c'*/
	cbreak();
	/* Line buffering disabled, Pass on everything to me; even 'ctrl + c'*/
	//raw();
	nonl();
	// gives the flexibility of echoing characters at any place in the window without updating current (y,x). turn off with echo()
	noecho();
	// It enables the reading of function keys like F1, F2, arrow keys etc for stdscr
	//keypad(input_window, TRUE);
	keypad(stdscr, TRUE);
	
	curs_set(0);

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);

	init_pair(2, COLOR_YELLOW, COLOR_BLACK);

	init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

IO::~IO()
{
	endwin();
}

void IO::render()
{
	// refresh() checks the window and updates only the portion which has been changed
	wrefresh(stdscr);
}

int IO::input(int to)
{
	wtimeout(stdscr, to);
	int keypress = wgetch(stdscr);

	return keypress;
}