CC     = gcc
CFLAGS = -Wall -c -I $(SRC_DIR)
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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@


test: $(TEST_EXE)

$(TEST_EXE): $(TEST_MAIN_OBJ) $(TEST_UTIL_OBJ) $(TEST_CASE_OBJ) $(OBJ)
	$(CC) $(TEST_MAIN_OBJ) $(TEST_UTIL_OBJ) $(TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(TEST_EXE)	

$(OBJ_DIR)%.o: $(TEST_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm $(OBJ_DIR)*.o $(EXE_DIR)$(EXE) $(EXE_DIR)$(TEST_EXE)
