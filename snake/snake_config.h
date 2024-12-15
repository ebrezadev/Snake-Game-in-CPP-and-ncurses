/*
This header file contains extern global objects and constant definitions related to field, snake length and snake speed
*/
#ifndef __SNAKE_CONFIG_H__
#define __SNAKE_CONFIG_H__

inline constexpr int MINIMUM_COLUMNS = 30;
inline constexpr int MINIMUM_ROWS = 15;

inline constexpr int MAX_FIELD_ROWS = 1000;
inline constexpr int MAX_FIELD_COLUMNS = 1000;

inline constexpr int DEFAULT_ROWS = 20;
inline constexpr int DEFAULT_COLUMNS = 40;

inline constexpr int DEFAULT_SNAKE_MINIMUM_LENGTH = 1;
inline constexpr int DEFAULT_SNAKE_MAXIMUM_LENGTH = 60;
inline constexpr int DEFAULT_SNAKE_MINIMUM_SPEED = 2;
inline constexpr int DEFAULT_SNAKE_MAXIMUM_SPEED = 30;

extern int field_rows;
extern int field_columns;
extern int x_offset;
extern int y_offset;

extern int snake_minimum_length;
extern int snake_maximum_length;
extern int snake_minimum_speed;
extern int snake_maximum_speed;

#endif