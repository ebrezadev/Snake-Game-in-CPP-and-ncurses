/*
This file includes global pre-defined state objects and state table used by the state machine.

Game specific.
*/
#include "states.h"

State_Main_Menu Main_Menu;
State_Settings Settings;
State_Loading Loading;
State_Game Game;
State_Pause_Menu Pause_Menu;
State_Finished Finished;
State_Screen_Error Screen_Error;
State_Exit Exit;

State *states_table[NUMBER_OF_STATES] = {
	&Main_Menu,
	&Settings,
	&Loading,
	&Game,
	&Pause_Menu,
	&Finished,
	&Screen_Error,
	&Exit};
