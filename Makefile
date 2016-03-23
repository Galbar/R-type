CC = g++
CFLAGS = -Wall -std=c++11 -O3
ODIR   := obj
SDIR   := src
INC    := -Iinclude -I../Hum2D/include -I../glm -I/opt/local/include/ -L/opt/local/lib/

SOURCES = $(shell find ./$(SDIR) -name '*.cpp')
OBJS = $(patsubst $(SDIR)/%,$(ODIR)/%,$(SOURCES:./%.cpp=%.o))

all: main.cpp $(OBJS)
	$(CC) -o game main.cpp $(ODIR)/*.o $(CFLAGS) $(INC) ../Hum2D/lib/libhum2d.a -lsfml-audio -lsfml-window -lsfml-system -lsfml-graphics -lGL -lGLEW

lib: $(OBJS)


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o game
