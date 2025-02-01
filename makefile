CC=gcc
CFLAGS=-Wall -c
EXE=terminal_tetris
OBJS=terminal_tetris.o

all: $(EXE)

terminal_tetris: $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

terminal_tetris.o: terminal_tetris.c
	$(CC) $(CFLAGS) terminal_tetris.c

clean:
	rm $(OBJS) $(EXE)
