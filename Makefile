TARGET = breakout
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = g++

all: breakout.o brick.o paddle.o color.o game.o vector.h
	$(CC) breakout.o game.o brick.o paddle.o color.o $(FLAGS) $(LIBS) -o $(TARGET)

$(TARGET): breakout.o brick.o paddle.o color.o game.o vector.h
	$(CC) breakout.o game.o brick.o paddle.o color.o $(FLAGS) $(LIBS) -o $(TARGET)

breakout.o: breakout.h breakout.cpp
	$(CC) breakout.cpp -c

brick.o: brick.h brick.cpp
	$(CC) brick.cpp -c

paddle.o: paddle.h paddle.cpp
	$(CC) paddle.cpp -c

color.o: color.h color.cpp
	$(CC) color.cpp -c

game.o: game.h game.cpp
	$(CC) game.cpp -c


clean:
	-rm -f *.o $(TARGET) *~ .*.swp
