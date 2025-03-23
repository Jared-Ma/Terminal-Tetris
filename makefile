CC     = gcc
CFLAGS = -Wall -c -std=gnu99
LIBS   = -lncurses -lm

EXE_DIR  = 
SRC_DIR  = src/
OBJ_DIR  = obj/
TEST_DIR = test/
TEST_UTILS_DIR = test/utils/

INCLUDE_SRC = -I $(SRC_DIR)
INCLUDE_TEST_UTIL = -I $(TEST_UTILS_DIR)

EXE      = terminal_tetris
MAIN_SRC = $(addprefix $(SRC_DIR), terminal_tetris.c)
SRC      = $(addprefix $(SRC_DIR), game_state.c draw.c vfx.c piece.c stats.c logger.c)
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(MAIN_SRC)))))
OBJ      = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(SRC)))))

UNIT_TEST_DIR      = $(TEST_DIR)unit/
UNIT_TEST_EXE      = unit_test_runner
UNIT_TEST_MAIN_SRC = $(addprefix $(UNIT_TEST_DIR), unit_test_runner.c)
UNIT_TEST_UTIL_SRC = $(addprefix $(UNIT_TEST_DIR), unit_test.c)
UNIT_TEST_CASE_SRC = $(addprefix $(UNIT_TEST_DIR), $(wildcard $(UNIT_TEST_DIR)test*.c))
UNIT_TEST_MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UNIT_TEST_MAIN_SRC)))))
UNIT_TEST_UTIL_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UNIT_TEST_UTIL_SRC)))))
UNIT_TEST_CASE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UNIT_TEST_CASE_SRC)))))

UI_TEST_DIR      = $(TEST_DIR)ui/
UI_TEST_EXE      = ui_test_runner
UI_TEST_MAIN_SRC = $(addprefix $(UI_TEST_DIR), ui_test_runner.c)
UI_TEST_UTIL_SRC = $(addprefix $(UI_TEST_DIR), ui_test.c)
UI_TEST_CASE_SRC = $(addprefix $(UI_TEST_DIR), $(wildcard $(UI_TEST_DIR)test*.c))
UI_TEST_MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UI_TEST_MAIN_SRC)))))
UI_TEST_UTIL_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UI_TEST_UTIL_SRC)))))
UI_TEST_CASE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(UI_TEST_CASE_SRC)))))

VFX_TEST_DIR      = $(TEST_DIR)vfx/
VFX_TEST_EXE      = vfx_test_runner
VFX_TEST_MAIN_SRC = $(addprefix $(VFX_TEST_DIR), vfx_test_runner.c)
VFX_TEST_UTIL_SRC = $(addprefix $(VFX_TEST_DIR), vfx_test.c)
VFX_TEST_CASE_SRC = $(addprefix $(VFX_TEST_DIR), $(wildcard $(VFX_TEST_DIR)test*.c))
VFX_TEST_MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(VFX_TEST_MAIN_SRC)))))
VFX_TEST_UTIL_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(VFX_TEST_UTIL_SRC)))))
VFX_TEST_CASE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(VFX_TEST_CASE_SRC)))))

PERF_TEST_DIR      = $(TEST_DIR)perf/
PERF_TEST_EXE      = perf_test_runner
PERF_TEST_MAIN_SRC = $(addprefix $(PERF_TEST_DIR), perf_test_runner.c)
PERF_TEST_UTIL_SRC = $(addprefix $(PERF_TEST_DIR), perf_test.c)
PERF_TEST_CASE_SRC = $(addprefix $(PERF_TEST_DIR), $(wildcard $(PERF_TEST_DIR)test*.c))
PERF_TEST_MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(PERF_TEST_MAIN_SRC)))))
PERF_TEST_UTIL_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(PERF_TEST_UTIL_SRC)))))
PERF_TEST_CASE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(notdir $(basename $(PERF_TEST_CASE_SRC)))))


all: $(EXE)

$(EXE): $(MAIN_OBJ) $(OBJ)
	$(CC) $(MAIN_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(EXE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@


unit_test: $(UNIT_TEST_EXE)

$(UNIT_TEST_EXE): $(UNIT_TEST_MAIN_OBJ) $(UNIT_TEST_UTIL_OBJ) $(UNIT_TEST_CASE_OBJ) $(OBJ)
	$(CC) $(UNIT_TEST_MAIN_OBJ) $(UNIT_TEST_UTIL_OBJ) $(UNIT_TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(UNIT_TEST_EXE)	

$(OBJ_DIR)unit_test_runner.o: $(UNIT_TEST_DIR)unit_test_runner.c
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ_DIR)unit_test.o: $(UNIT_TEST_DIR)unit_test.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)test%.o: $(UNIT_TEST_DIR)test%.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $(INCLUDE_TEST_UTIL) $< -o $@


ui_test: $(UI_TEST_EXE)

$(UI_TEST_EXE): $(UI_TEST_MAIN_OBJ) $(UI_TEST_UTIL_OBJ) $(UI_TEST_CASE_OBJ) $(OBJ)
	$(CC) $(UI_TEST_MAIN_OBJ) $(UI_TEST_UTIL_OBJ) $(UI_TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(UI_TEST_EXE)	

$(OBJ_DIR)ui_test_runner.o: $(UI_TEST_DIR)ui_test_runner.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $< -o $@

$(OBJ_DIR)ui_test.o: $(UI_TEST_DIR)ui_test.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)test%.o: $(UI_TEST_DIR)test%.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $(INCLUDE_TEST_UTIL) $< -o $@


vfx_test: $(VFX_TEST_EXE)

$(VFX_TEST_EXE): $(VFX_TEST_MAIN_OBJ) $(VFX_TEST_UTIL_OBJ) $(VFX_TEST_CASE_OBJ) $(OBJ)
	$(CC) $(VFX_TEST_MAIN_OBJ) $(VFX_TEST_UTIL_OBJ) $(VFX_TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(VFX_TEST_EXE)	

$(OBJ_DIR)vfx_test_runner.o: $(VFX_TEST_DIR)vfx_test_runner.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $< -o $@

$(OBJ_DIR)vfx_test.o: $(VFX_TEST_DIR)vfx_test.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $< -o $@

$(OBJ_DIR)test%.o: $(VFX_TEST_DIR)test%.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $(INCLUDE_TEST_UTIL) $< -o $@


perf_test: $(PERF_TEST_EXE)

$(PERF_TEST_EXE): $(PERF_TEST_MAIN_OBJ) $(PERF_TEST_UTIL_OBJ) $(PERF_TEST_CASE_OBJ) $(OBJ)
	$(CC) $(PERF_TEST_MAIN_OBJ) $(PERF_TEST_UTIL_OBJ) $(PERF_TEST_CASE_OBJ) $(OBJ) $(LIBS) -o $(EXE_DIR)$(PERF_TEST_EXE)	

$(OBJ_DIR)perf_test_runner.o: $(PERF_TEST_DIR)perf_test_runner.c
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJ_DIR)perf_test.o: $(PERF_TEST_DIR)perf_test.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)test%.o: $(PERF_TEST_DIR)test%.c
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $(INCLUDE_TEST_UTIL) $< -o $@


clean:
	rm $(OBJ_DIR)*.o $(EXE_DIR)$(EXE) $(EXE_DIR)$(UNIT_TEST_EXE) $(EXE_DIR)$(UI_TEST_EXE) $(EXE_DIR)$(VFX_TEST_EXE)
