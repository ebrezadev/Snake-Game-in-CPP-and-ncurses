/*
This header file contains the class definitions for all state classes.

Game specific.
*/
#ifndef __STATES_H__
#define __STATES_H__

#include "state_interface.h"
#include "state_list.h"
#include "field.h"
#include "snake.h"
#include "food.h"
#include "snake_config.h"
#include "fps.h"
#include <queue>

inline constexpr int NUMBER_OF_EVENTS = 6;
inline constexpr int NUMBER_OF_STATES = 8;

// All possible input events
enum class Input_t
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	ENTER,
	NONE
};

class State_Main_Menu : public State
{
public:
	State_Main_Menu();
	state_return_t stateFunction(int input);

private:
	enum class menu_t
	{
		START_GAME,
		SETTINGS,
		EXIT
	};
	menu_t current_menu;
};

class State_Settings : public State
{
public:
	State_Settings();
	state_return_t stateFunction(int input);

private:
	enum class menu_t
	{
		ROWS_SETTING,
		COLUMNS_SETTING,
		SNAKE_MIN_LENGTH_SETTING,
		SNAKE_MAX_LENGTH_SETTING,
		SNAKE_MIN_SPEED_SETTING,
		SNAKE_MAX_SPEED_SETTING,
		BACK
	};
	menu_t current_menu;
};

class State_Loading : public State
{
public:
	State_Loading();
	state_return_t stateFunction(int input);

private:
};

class State_Game : public State
{
public:
	State_Game();
	~State_Game() {};
	state_return_t stateFunction(int input);
	void reset();

private:
	Field *field;
	Snake *snake;
	Food *food;
	std::queue<int> input_fifo;
};

class State_Pause_Menu : public State
{
public:
	State_Pause_Menu();
	~State_Pause_Menu() {};
	state_return_t stateFunction(int input);

private:
enum class menu_t
	{
		CONTINUE,
		MAIN_MENU,
		EXIT
	};
	
	menu_t current_menu;
};

class State_Exit : public State
{
public:
	State_Exit();
	~State_Exit() {};
	state_return_t stateFunction(int input);

private:
};

class State_Finished : public State
{
public:
	State_Finished();
	~State_Finished() {};
	state_return_t stateFunction(int input);
	friend class State_Game;
	
private:
	bool has_won;
};

class State_Screen_Error : public State
{
public:
	State_Screen_Error();
	~State_Screen_Error() {};
	state_return_t stateFunction(int input);

private:
};

extern State *states_table[NUMBER_OF_STATES];

extern State_Main_Menu Main_Menu;
extern State_Settings Settings;
extern State_Loading Loading;
extern State_Game Game;
extern State_Pause_Menu Pause_Menu;
extern State_Finished Finished;
extern State_Screen_Error Screen_Error;
extern State_Exit Exit;

#endif
