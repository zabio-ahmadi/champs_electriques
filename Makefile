CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=address  -fsanitize=address
LDFLAGS=-lSDL2 -lm -O3
VPATH:=utils/vec2/ utils/gfx/ utils
all: champ 

champ: main.o gfx.o champ.o vec2.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

gfx.o: gfx.h
utils.o: utils.h
champ.o: champ.h vec2.h utils.h
vec2.o: vec2.h
main.o: champ.h gfx.h utils.h

clean:
	rm -f champ *.o

rebuild: clean all

make run: 
	./champ