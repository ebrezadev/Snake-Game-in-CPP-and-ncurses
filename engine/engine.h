/* 
This file contains 'game engine' class. Game begins with instantiating and running an engine object.
engine class is a singleton class to stop duplicate engine objects.

Platform/Game/IO independent.
*/
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "io.h"
#include "state_machine.h"
#include "fps.h"

// Engine is responsible for high level game loop
class Engine
{
public:
	static Engine &getInstance();
	Engine(Engine &other) = delete;				
	void operator=(const Engine &) = delete;
	void execute();									// Runs the game loop

private:
	Engine();
	~Engine();
	void update(int to);						// Passes the input to state machine
	void render();								// Updates the screen 
	void sleep(int ms);		
	bool is_running;							// Finished game condition
	bool should_update;							// Determines if engine should render. Helps with unnecessary stuttering while stationary
	IO *io;										// pointer to IO object
	StateMachine gameStateMachine;				// State Machine object
};

#endif