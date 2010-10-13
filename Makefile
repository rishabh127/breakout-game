TARGET = breakout
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = gcc
CPP = g++

all: breakout.o game.o ball.o brick.o paddle.o color.o vector.h entity.o image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o
	$(CPP) breakout.o game.o ball.o brick.o paddle.o color.o entity.o image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o $(FLAGS) $(LIBS) -o $(TARGET)

breakout.o: breakout.h breakout.cpp
	$(CPP) $(FLAGS) breakout.cpp -c

game.o: game.h game.cpp
	$(CPP) $(FLAGS) game.cpp -c

brick.o: brick.h brick.cpp
	$(CPP) $(FLAGS) brick.cpp -c

paddle.o: paddle.h paddle.cpp
	$(CPP) $(FLAGS) paddle.cpp -c
	
ball.o: ball.h ball.cpp
	$(CPP) $(FLAGS) ball.cpp -c

color.o: color.h color.cpp
	$(CPP) $(FLAGS) color.cpp -c

entity.o: entity.h entity.cpp
	$(CPP) $(FLAGS) entity.cpp -c
	
	
# 	SOIL - texture

glTexture.o: glTexture.cpp
	$(CPP) -c $(FLAGS) glTexture.cpp -o glTexture.o

SOIL.o: soil/SOIL.c
	$(CC) -c $(FLAGS) soil/SOIL.c 

image_DXT.o: soil/image_DXT.c 
	$(CC) -c $(FLAGS) soil/image_DXT.c 

image_helper.o: soil/image_helper.c 
	$(CC) -c $(FLAGS) soil/image_helper.c 

stb_image_aug.o: soil/stb_image_aug.c
	$(CC) -c $(FLAGS) soil/stb_image_aug.c
	

clean:
	-rm -f *.o $(TARGET) *~ .*.swp
