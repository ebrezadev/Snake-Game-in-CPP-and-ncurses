/*
This file includes the class description for DrawString, 
used for drawing titles and big fonts.
*/
#ifndef __ALPHABET_DRAW_H__
#define __ALPHABET_DRAW_H__

class DrawString{
public:
	static void drawString(char *str, int start_x, int start_y);
	
private:
	typedef bool alphabet_matrix[5][5];	
	static const alphabet_matrix alphabet_table[59];
};


#endif