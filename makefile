CC     = gcc
CFLAGS = -Wall -c
LIBS   = -lncurses -lm

EXE_DIR  = 
SRC_DIR  = src/
OBJ_DIR  = obj/
TEST_DIR = test/

EXE      = terminal_tetris
MAIN_SRC = $(addprefix $(SRC_DIR), terminal_tetris.c)
SRC      = $(addprefix $(SRC_DIR), game_state.c draw.c piece.c stats.c logger.c)
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(MAIN_SRC)))))
OBJ      = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(SRC)))))

TEST_EXE      = test_runner
TEST_MAIN_SRC = $(addprefix $(TEST_DIR), test_runner.c)
TEST_UTIL_SRC = $(addprefix $(TEST_DIR), unit_test.c)
TEST_CASE_SRC = $(addprefix $(TEST_DIR), test_piece.c)
TEST_MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(TEST_MAIN_SRC)))))
TEST_UTIL_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(TEST_UTIL_SRC)))))
TEST_CASE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(TEST_CASE_SRC)))))


all: $(EXE)

$(EXE): $(MAIN_OBJ) $(OBJ)
	$(CC) $(MAIN_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(EXE)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $@

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


test: $(TEST_EXE)

$(TEST_EXE): $(TEST_MAIN_OBJ) $(TEST_UTIL_OBJ) $(TEST_CASE_OBJ) $(OBJ)
	$(CC) $(TEST_MAIN_OBJ) $(TEST_UTIL_OBJ) $(TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(TEST_EXE)	

$(TEST_MAIN_OBJ): $(TEST_MAIN_SRC)
	$(CC) $(CFLAGS) $(TEST_MAIN_SRC) -o $@

$(OBJ_DIR)unit_test.o: $(TEST_DIR)unit_test.c
	$(CC) $(CFLAGS) $(TEST_DIR)unit_test.c -o $@

$(OBJ_DIR)test_piece.o: $(TEST_DIR)test_piece.c 
	$(CC) $(CFLAGS) $(TEST_DIR)test_piece.c -o $@


clean:
	rm $(OBJ_DIR)*.o $(EXE_DIR)$(EXE) $(EXE_DIR)$(TEST_EXE)
