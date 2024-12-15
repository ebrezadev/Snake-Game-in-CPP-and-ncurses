#include "field.h"
#include <ncurses.h>

int field_rows;
int field_columns;
int x_offset;
int y_offset;

Field::Field()
{
	// Filling the cell_direction matrix with a default value of RIGHT
	for (int i = 0; i < field_rows; i++)
	{
		for (int j = 0; j < field_columns; j++)
		{
			cell_direction[i][j] = direction_t::RIGHT;
		}
	}
}

void Field::printWalls()
{
	for (int i = 0; i < (field_rows + 2); i++)
	{
		for (int j = 0; j < (field_columns + 2); j++)
		{
			if ((i == 0) && (j == 0))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_BSSB);
			}
			else if((i == 0) && (j == (field_columns + 1)))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_BBSS);
			}
			else if((i == (field_rows + 1)) && (j == 0))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_SSBB);
			}
			else if((i == (field_rows + 1)) && (j == (field_columns + 1)))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_SBBS);
			}
			else if ((i == 0) || (i == (field_rows + 1)))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_HLINE);
			}
			else if ((j == 0) || (j == (field_columns + 1)))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_VLINE);
			}
		}
	}
}