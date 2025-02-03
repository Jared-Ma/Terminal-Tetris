CC=gcc
CFLAGS=-Wall -c
EXE=terminal_tetris
OBJS=terminal_tetris.o draw.o piece.o
LIBS= -lncurses

all: $(EXE)

terminal_tetris: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(EXE)

terminal_tetris.o: terminal_tetris.c
	$(CC) $(CFLAGS) terminal_tetris.c

draw.o: draw.c
	$(CC) $(CFLAGS) draw.c

piece.o: piece.c
	$(CC) $(CFLAGS) piece.c

clean:
	rm $(OBJS) $(EXE)
