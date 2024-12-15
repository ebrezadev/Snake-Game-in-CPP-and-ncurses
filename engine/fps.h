/*
This header file contains and exposes necessary 'Frames Per Second' and timing globals.
Used by 'engine' to determine periods and timeouts. 

Platform/Game/IO independent.
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__

inline constexpr int DEFAULT_FPS = 200;

extern int FPS;
extern int period_ms;
extern int input_timeout_ms;
extern int sleep_ms;

#endif
