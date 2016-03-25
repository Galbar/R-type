CC = g++
CFLAGS = -Wall -std=c++11 -O3
ODIR   := obj
SDIR   := src
INC    := -Iinclude -I../Hum2D/include -I../MOGL/include -I../glm -I/opt/local/include/ -I../tiled/include
LIBS   := -L/opt/local/lib/ -lsfml-audio -lsfml-window -lsfml-system -lsfml-graphics -lGL -lGLEW
STATIC := ../Hum2D/lib/libhum2d.a ../MOGL/lib/libmogl.a ../tiled/lib/libtiled.a

SOURCES = $(shell find ./$(SDIR) -name '*.cpp')
OBJS = $(patsubst $(SDIR)/%,$(ODIR)/%,$(SOURCES:./%.cpp=%.o))

all: $(OBJS)
	$(CC) -o game $(OBJS) $(CFLAGS) $(INC) $(STATIC) $(LIBS)

test: test.cpp $(OBJS)
	$(CC) -o test test.cpp $(OBJS) $(CFLAGS) $(INC) $(STATIC) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o game
