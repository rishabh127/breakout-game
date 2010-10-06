TARGET = breakout
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm -g
FLAGS = -Wall -g
CC = g++

all: breakout.o game.o ball.o brick.o paddle.o color.o vector.h entity.o 
	$(CC) breakout.o game.o ball.o brick.o paddle.o color.o entity.o $(FLAGS) $(LIBS) -o $(TARGET)

breakout.o: breakout.h breakout.cpp
	$(CC) $(FLAGS) breakout.cpp -c

game.o: game.h game.cpp
	$(CC) $(FLAGS) game.cpp -c

brick.o: brick.h brick.cpp
	$(CC) $(FLAGS) brick.cpp -c

paddle.o: paddle.h paddle.cpp
	$(CC) $(FLAGS) paddle.cpp -c
	
ball.o: ball.h ball.cpp
	$(CC) $(FLAGS) ball.cpp -c

color.o: color.h color.cpp
	$(CC) $(FLAGS) color.cpp -c

entity.o: entity.h entity.cpp
	$(CC) $(FLAGS) entity.cpp -c


clean:
	-rm -f *.o $(TARGET) *~ .*.swp
