CC = g++
CFLAGS = -Wall -std=c++11 -O3
INC    := -I../Hum2D/include -I../glm

all: main.cpp
	$(CC) -o game main.cpp $(CFLAGS) $(INC) ../Hum2D/lib/libhum2d.a -lsfml-audio -lsfml-window -lsfml-system

