/*
This file contains a type definition for list of states. 
Used in state machine.
*/

#ifndef __STATE_LIST_H__
#define __STATE_LIST_H__

enum class State_list_t
{
	State_Main_Menu,
	State_Settings,
	State_Loading,
	State_Game,
	State_Pause_Menu,
	State_Finished,
	State_Screen_Error,
	State_Exit
};

#endif
