#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "piece.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/** @file
 ** @brief Constants that describe the parameters of the game, and the functions 
 ** that interface with and modify the GameState object. 
 **/

// Height at which buffer zone is defined
#define BUFFER_ZONE_H 2

// Dimensions of game board.
#define BOARD_H 22
#define BOARD_W 10

// Dimensions of SRS tables.
#define SRS_NUM_ROTATIONS 8
#define SRS_NUM_TESTS 5
#define SRS_NUM_COORDS 2

// Max level where gravity caps out. 
#define MAX_GRAVITY_LEVEL 15


extern const int8_t SPAWN_Y;
extern const int8_t SPAWN_X;

extern const uint8_t LEVEL_LINE_REQ;
extern const uint8_t LOCK_DELAY;
extern const uint8_t MAX_MOVE_RESET;
extern const uint8_t SOFT_DROP_GRAVITY_MULT;

extern const uint16_t SINGLE_POINTS;
extern const uint16_t DOUBLE_POINTS;
extern const uint16_t TRIPLE_POINTS;
extern const uint16_t TETRIS_POINTS;

extern const uint16_t T_SPIN_ZERO_POINTS;
extern const uint16_t T_SPIN_SINGLE_POINTS;
extern const uint16_t T_SPIN_DOUBLE_POINTS;
extern const uint16_t T_SPIN_TRIPLE_POINTS;

extern const uint16_t T_SPIN_MINI_ZERO_POINTS;
extern const uint16_t T_SPIN_MINI_SINGLE_POINTS;
extern const uint16_t T_SPIN_MINI_DOUBLE_POINTS;

extern const uint16_t SINGLE_ALL_CLEAR_POINTS;
extern const uint16_t DOUBLE_ALL_CLEAR_POINTS;
extern const uint16_t TRIPLE_ALL_CLEAR_POINTS;
extern const uint16_t TETRIS_ALL_CLEAR_POINTS;
extern const uint16_t B2B_TETRIS_ALL_CLEAR_POINTS;

extern const uint16_t COMBO_POINTS;
extern const uint16_t SOFT_DROP_POINTS;
extern const uint16_t HARD_DROP_POINTS;
extern const float B2B_DIFFICULT_CLEAR_MULT;

extern const int8_t SRS_TABLE[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
extern const int8_t SRS_TABLE_I[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
extern const int8_t SRS_TABLE_O[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];

extern const float GRAVITY_TABLE[MAX_GRAVITY_LEVEL];

/**
 ** @brief GameState consists of all the variables that are necessary to 
 ** maintaining and keeping track of the current game state.
 **/
struct GameState {
    Piece curr_piece;
    Piece hold_piece;
    Piece next_piece;
    Piece ghost_piece;
    Shape board[BOARD_H][BOARD_W];

    bool holding_piece;
    bool hold_blocked;
    uint8_t next_index;
    Shape next_queue[NUM_SHAPES];

    bool soft_drop;
    float gravity_value;
    uint8_t lock_delay_timer;
    uint8_t move_reset_count;

    uint16_t level;
    uint32_t lines;
    uint64_t score;
    int16_t combo;
    int16_t difficult_clear_combo;
    int16_t tetris_all_clear_combo;
    uint8_t t_rotation_test_num;

    uint32_t last_action_points;
    uint8_t last_action_num_lines;
    bool last_action_t_spin;
    bool last_action_t_spin_mini;
    bool last_action_all_clear;
    bool hold_piece_event_flag;
    bool next_piece_event_flag;
    bool level_up_event_flag;
    Shape last_locked_piece_shape;
};

typedef struct GameState GameState;


/** 
 ** @brief Initialize the GameState object.
 **
 ** @return The initialized GameState object.
 **/
GameState game_state_get(void);

/** 
 ** @brief Allocate memory and initialize a GameState object.
 **
 ** @return A pointer to the allocated GameState object.
 **/
GameState* game_state_init(void);

/** 
 ** @brief Deallocate the GameState object @game_state.
 **
 ** @param game_state The GameState object to be deallocated.
 **/
void game_state_destroy(GameState* game_state);

/** 
 ** @brief Print values of each member in @game_state.
 **
 ** @param game_state The GameState object to be read. 
 **/
void game_state_debug_print(const GameState* game_state);

/** 
 ** @brief Set initial game start values of @game_state.
 ** 
 ** @param game_state The GameState object to be modified.
 ** @param start_level The level that will be set to.
 **/
void game_state_start(GameState* game_state, uint8_t start_level);

/** 
 ** @brief Reset values of @game_state to what they were on initialization.
 **
 ** @param game_state The GameState object to be reset.
 **/
void game_state_reset(GameState* game_state);

/** 
 ** @brief Reset the values used for checking conditions and enabling VFX.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_reset_vfx_conditions(GameState* game_state);

/** 
 ** @brief Randomly generate a permutation of the 7 possible piece shapes.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_generate_next_queue(GameState* game_state);

/** 
 ** @brief Set current piece to the next piece in the queue, assign subsequent 
 ** next piece, and generate next queue if no more pieces left.
 ** 
 ** @param game_state The GameState object to be modified.
 **/
void game_state_load_next_piece(GameState* game_state);

/** 
 ** @brief Set spawn values of current piece, update ghost piece, and set 
 ** initial playing piece property values.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_spawn_curr_piece(GameState* game_state);

/** 
 ** @brief Swap current piece with piece currently being held, or if there is 
 ** no held piece, set current piece to held piece and load next piece.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_hold_piece(GameState* game_state);

/** 
 ** @brief Check whether @piece collides with boundaries of board or board 
 ** stack. 
 ** 
 ** @param game_state The GameState object to be read from.
 ** @param piece The piece to check collision on.
 **
 ** @return True if collision detected, otherwise False.
 **/
bool game_state_check_collision(const GameState* game_state, Piece piece);

/** 
 ** @brief Check whether the current piece is directly above the bottom of the 
 ** board, or the board stack
 ** 
 ** @param game_state The GameState object to be read from.
 ** 
 ** @return True if current piece grounded, otherwise False. 
 **/
bool game_state_check_curr_piece_grounded(const GameState* game_state);

/** 
 ** @brief Move current piece to the location (@y, @x) if not impeded, update 
 ** ghost piece position, and reset lock delay timer if lock delay has been 
 ** decremented before and move reset count has not reached maximum. 
 ** 
 ** @param game_state The GameState object to be modified. 
 ** @param y The y-coordinate to move piece to. 
 ** @param x The x-coordinate to move piece to. 
 **/
void game_state_move_curr_piece(GameState* game_state, int8_t y, int8_t x);

/** 
 ** @brief Rotate current piece either left or right according to @rotation if
 ** not impeded.
 **
 ** @param game_state The GameState object to be modified.
 ** @param rotation The direction to rotate the piece in.
 **/
void game_state_rotate_curr_piece(GameState* game_state, Rotation rotation);

/** 
 ** @brief Rotate current piece by going through series of SRS tests and 
 ** accepting the first SRS test passed, where each test translates the piece
 ** a short distance.
 **
 ** @param game_state The GameState object to be modified.
 ** @param rotation The direction to rotate the piece in.
 **/
void game_state_rotate_curr_piece_srs(GameState* game_state, Rotation rotation);

/** 
 ** @brief Move current piece directly down stopping on the first collision, 
 ** setting lock delay timer to 0, and adding corresponding points to score.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_hard_drop_curr_piece(GameState* game_state);

/** 
 ** @brief Add current piece's values to the board, and unblock holding. 
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_lock_curr_piece(GameState* game_state);

/** 
 ** @brief Shifts all cells that are above @row one line down.
 **
 ** @param game_state The GameState object to be modified.
 ** @param row The row at which stack gravity will be applied
 **/
void game_state_apply_stack_gravity(GameState* game_state, uint8_t row);

/** 
 ** @brief Clear line of the game board at @row.
 **
 ** @param game_state The GameState object to be modified.
 ** @param row The row at which the line will be cleared.
 **/
void game_state_clear_line(GameState* game_state, uint8_t row);

/** 
 ** @brief Clear all detected lines on current board, apply stack gravity, add 
 ** corresponding points, update number of lines, and level up if conditions 
 ** are met.
 **  
 ** @param game_state The GameState object to be modified.
 **/
void game_state_clear_lines(GameState* game_state);

/** 
 ** @brief Add to current piece's gravity value according to the current level, 
 ** and move piece down by as many cells equal to the integer part of the 
 ** gravity value. 
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_apply_gravity(GameState* game_state);

/** 
 ** @brief Add to current piece's gravity value according to the current level
 ** multiplied by the soft drop gravity multiplier, apply gravity, and add 
 ** corresponding points to score.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_apply_soft_drop_gravity(GameState* game_state);

/** 
 ** @brief Move current piece 1 cell down, toggle soft drop flag to be true, and
 ** add corresponding points.
 **
 ** @param game_state The GameState object to be modified. 
 **/
void game_state_soft_drop_curr_piece(GameState* game_state);

/** 
 ** @brief Update the position of ghost piece relative to the current piece's 
 ** position.
 **
 ** @param game_state The GameState object to be modified.
 **/
void game_state_update_ghost_piece(GameState* game_state);

/** 
 ** @brief Check a series of conditions that detect whether a t-spin occurred.
 **
 ** @param game_state The GameState object to be read from.
 ** 
 ** @return True if t-spin detected, otherwise False.
 **/
bool game_state_check_t_spin(const GameState* game_state);

/** 
 ** @brief Check a series of conditions that detect whether a t-spin mini 
 ** occurred.
 **
 ** @param game_state The GameState object to be read from.
 ** 
 ** @return True if t-spin mini detected, otherwise False.
 **/
bool game_state_check_t_spin_mini(const GameState* game_state);

/** 
 ** @brief Check whether the board is empty.
 **
 ** @param game_state The GameState object to be read from
 **
 ** @return True if board empty, otherwise False.
 **/
bool game_state_check_empty_board(const GameState* game_state);

/** 
 ** @brief Calculate the number of points to add to score if a t-spin occurred,
 ** and keep track of back-to-back difficult clear combo.
 **
 ** @param game_state The GameState object to be modified.
 ** @param num_lines The number of lines cleared on the last action.
 **
 ** @return The number of points to add.
 **/
uint32_t game_state_calc_t_spin_points(GameState* game_state, uint8_t num_lines);

/** 
 ** @brief Calculate the number of points to add on line clear, and keep track
 ** of back-to-back difficult clear combo.
 **
 ** @param game_state The GameState object to be modified.
 ** @param num_lines The number of lines cleared on the last action.
 **
 ** @return The number of points to add.
 **/
uint32_t game_state_calc_line_clear_points(GameState* game_state, uint8_t num_lines);

/** 
 ** @brief Calculate the number of points to add on an all/perfect clear, and
 ** keep track of the tetris all/perfect clear combo.
 **
 ** @param game_state The GameState object to be modified.
 ** @param num_lines The number of lines cleared on the last action.
 **
 ** @return The number of points to add.
 **/
uint32_t game_state_calc_all_clear_points(GameState* game_state, uint8_t num_lines);

/** 
 ** @brief Calculate the number of points to add on combos, and keep track of 
 ** the combo counter.
 **
 ** @param game_state The GameState object to be modified.
 ** @param num_lines The number of lines cleared on the last action.
 **
 ** @return The number of points to add.
 **/
uint32_t game_state_calc_combo_points(GameState* game_state, uint8_t num_lines);

/** 
 ** @brief Calculate the point multiplier to use on back-to-back difficult clear
 ** combos.
 **
 ** @param game_state The GameState object to be modified.
 ** @param num_lines The number of lines cleared on the last action.
 **
 ** @return The point multiplier.
 **/
float game_state_calc_difficult_clear_mult(GameState* game_state, uint8_t num_lines);

#endif
