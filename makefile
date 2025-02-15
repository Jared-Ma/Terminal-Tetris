CC=gcc
CFLAGS=-Wall -c
EXE=terminal_tetris
OBJS=terminal_tetris.o game_state.o draw.o piece.o stats.o logger.o
LIBS= -lncurses -lm

all: $(EXE)

terminal_tetris: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(EXE)

terminal_tetris.o: terminal_tetris.c
	$(CC) $(CFLAGS) terminal_tetris.c

game_state.o: game_state.c
	$(CC) $(CFLAGS) game_state.c

draw.o: draw.c
	$(CC) $(CFLAGS) draw.c

piece.o: piece.c
	$(CC) $(CFLAGS) piece.c

stats.o: stats.c
	$(CC) $(CFLAGS) stats.c

logger.o: logger.c
	$(CC) $(CFLAGS) logger.c

clean:
	rm $(OBJS) $(EXE)
