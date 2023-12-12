exec = bin/server.o
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic -I./include

$(exec): $(objects)
	gcc $(objects) -o $(exec)

clean:
	rm src/*.o
