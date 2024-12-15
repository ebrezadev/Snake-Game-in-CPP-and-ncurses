all:
	g++ -Wall -Iengine -Iio -Isnake -I. engine/*.cpp io/*.cpp snake/*.cpp main.cpp -lncurses -o release/snake.out
