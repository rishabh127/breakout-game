TARGET = breakout
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = g++

all: breakout.o game.o ball.o brick.o paddle.o color.o vector.h entity.o 
	$(CC) breakout.o game.o ball.o brick.o paddle.o color.o entity.o $(FLAGS) $(LIBS) -o $(TARGET)

breakout.o: breakout.h breakout.cpp
	$(CC) breakout.cpp -c

game.o: game.h game.cpp
	$(CC) game.cpp -c

brick.o: brick.h brick.cpp
	$(CC) brick.cpp -c

paddle.o: paddle.h paddle.cpp
	$(CC) paddle.cpp -c
	
ball.o: ball.h ball.cpp
	$(CC) ball.cpp -c

color.o: color.h color.cpp
	$(CC) color.cpp -c

entity.o: entity.h entity.cpp
	$(CC) entity.cpp -c


clean:
	-rm -f *.o $(TARGET) *~ .*.swp
