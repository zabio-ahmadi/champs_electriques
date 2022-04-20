CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=address  -fsanitize=address
LIBS=-lSDL2 -lm -O3

all: champ

champ_header: champ.c champ.h
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

champ: main.c champ.o utils/gfx/gfx.c utils/vec2/vec2.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f champ champ.o

make run: 
	./champ