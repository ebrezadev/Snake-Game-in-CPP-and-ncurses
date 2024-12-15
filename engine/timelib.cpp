#include "timelib.h"
#include <chrono>
#include <thread>

int64_t timelib::milliseconds(){
	// Get the current time from the system clock
    auto now = std::chrono::system_clock::now();

    // Convert the current time to time since epoch
    auto duration = now.time_since_epoch();

    // Convert duration to milliseconds
    auto millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return millisecond;
}

void timelib::sleepMillis(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}