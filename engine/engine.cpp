#include <iostream>
#include "engine.h"
#include "timelib.h"
#include <ncurses.h>
int FPS = DEFAULT_FPS;
int period_ms;
int input_timeout_ms;
int sleep_ms;

Engine::Engine()
{
	// Initialize singleton io object
	io = IO::getInstance();

	// Initialize timings based on default FPS
	period_ms = 1000 / FPS;
	input_timeout_ms = (period_ms * 3) / 4;
	sleep_ms = period_ms / 5;

	is_running = true;
}

Engine::~Engine()
{
}

Engine &Engine::getInstance()
{
	static Engine Instance;
	return Instance;
}

void Engine::update(int to)
{
	// Read the input event from IO subsystem, with specified timeout
	int input = io->input(to);

	// Pass the input event to the state machine and run the state machine
	StateMachine::state_machine_return_t state_machine_return = gameStateMachine.run(input);

	is_running = state_machine_return.is_running;
	should_update = state_machine_return.update;
}

void Engine::render()
{
	io->render();
}

void Engine::sleep(int ms)
{
	timelib::sleepMillis(ms);
}

void Engine::execute()
{
	// Render the scene each PERIOD_MS (in milliseconds)
	int64_t previous = 0;

	// Main engine loop
	for (; is_running;)
	{
		// Read input from IO subsystem and pass it to state machine
		update(input_timeout_ms);

		sleep(sleep_ms);

		// Render the page for every period_ms, in case of 'should_update'
		auto now = timelib::milliseconds();
		if (((now - previous) >= period_ms) && should_update)
		{

			//mvprintw(0, 0, "period=%d FPS=%d sleep=%d diff=%d", period_ms, FPS, sleep_ms, (int)(now - previous));
			render();
			previous = now;
		}
	}
}
