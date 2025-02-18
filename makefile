CC = gcc
CFLAGS = -Wall -c
LIBS = -lncurses -lm

EXE = terminal_tetris
OBJS = $(addprefix $(OBJ_DIR), terminal_tetris.o game_state.o draw.o piece.o stats.o logger.o)

SRC_DIR = ./src/
OBJ_DIR = ./obj/
EXE_DIR = ./

all: $(EXE)

$(EXE): $(OBJ_DIR) m$(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o $(EXE_DIR)$(EXE)

$(OBJ_DIR)terminal_tetris.o: $(SRC_DIR)terminal_tetris.c
	$(CC) $(CFLAGS) $(SRC_DIR)terminal_tetris.c -o $@

$(OBJ_DIR)game_state.o: $(SRC_DIR)game_state.c
	$(CC) $(CFLAGS) $(SRC_DIR)game_state.c -o $@

$(OBJ_DIR)draw.o: $(SRC_DIR)draw.c
	$(CC) $(CFLAGS) $(SRC_DIR)draw.c -o $@

$(OBJ_DIR)piece.o: $(SRC_DIR)piece.c
	$(CC) $(CFLAGS) $(SRC_DIR)piece.c -o $@

$(OBJ_DIR)stats.o: $(SRC_DIR)stats.c
	$(CC) $(CFLAGS) $(SRC_DIR)stats.c -o $@

$(OBJ_DIR)logger.o: $(SRC_DIR)logger.c
	$(CC) $(CFLAGS) $(SRC_DIR)logger.c -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm $(OBJS) $(EXE_DIR)$(EXE)
