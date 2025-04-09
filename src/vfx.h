#ifndef VFX_H
#define VFX_H
#include "draw.h"
#include "game_state.h"

#include <stdbool.h>
#include <stdint.h>

/** @file
 ** @brief Constants that describe the parameters of the game VFX, and the 
 ** functions that interface with and modify the VFX object. 
 **/

// Total number of VFX in the game.
#define NUM_VFX 11

// Max length of VFX text. 
#define VFX_TEXT_MAX 64


extern const uint16_t LOCK_PIECE_VFX_FRAMES;
extern const uint16_t LINE_CLEAR_VFX_FRAMES;
extern const uint16_t HOLD_PIECE_VFX_FRAMES;
extern const uint16_t NEXT_PIECE_VFX_FRAMES;
extern const uint16_t ACTION_VFX_FRAMES;
extern const uint16_t COMBO_VFX_FRAMES;
extern const uint16_t B2B_COMBO_VFX_FRAMES;
extern const uint16_t POINTS_VFX_FRAMES;
extern const uint16_t LEVEL_UP_VFX_FRAMES;
extern const uint16_t STATS_LINES_VFX_FRAMES;
extern const uint16_t STATS_LEVEL_VFX_FRAMES;

extern const int8_t LEVEL_UP_VFX_Y;
extern const int8_t LEVEL_UP_VFX_W;

// Forward declaration of VFX.
struct VFX;

typedef struct VFX VFX;

typedef void vfx_draw_function(VFX* vfx);

typedef bool vfx_cond_function(VFX* vfx, const GameState* game_state);

typedef void vfx_enable_function(VFX* vfx, const GameState* game_state);

/** 
 ** @brief VFX consists of which window the VFX is drawn to, callback functions 
 ** for the VFX, how long the VFX is played, and where and what is printed if
 ** required.
 **/ 
struct VFX {
    GameWindow* game_window;
    vfx_draw_function* draw_vfx;
    vfx_draw_function* clear_vfx;
    vfx_cond_function* check_cond;
    vfx_enable_function* enable_vfx;
    uint16_t frame_timer;
    uint16_t frame_duration;
    bool enabled;
    int8_t y;
    int8_t x;
    char text[VFX_TEXT_MAX];
};

/**
 ** @brief Initialize the VFX object.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param clear_function The callback for when the VFX is finished.
 ** @param cond_function The callback to check if VFX should be enabled.
 ** @param enable_function The callback to enable the VFX.
 ** @param frame_duration The number of frames the VFX will be played for.
 **
 ** @return The initialized VFX object.
 **/
VFX vfx_get(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
);

/**
 ** @brief Allocate memory and initialize a VFX object.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param clear_function The callback for when the VFX is finished.
 ** @param cond_function The callback to check if VFX should be enabled.
 ** @param enable_function The callback to enable the VFX.
 ** @param frame_duration The number of frames the VFX will be played for.
 **
 ** @return A pointer to the allocated VFX object.
 **/
VFX* vfx_init(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
);

/** 
 ** @brief Deallocate the VFX object @vfx.
 **
 ** @param vfx The VFX object to be deallocated.
 **/
void vfx_destroy(VFX* vfx);

/** 
 ** @brief Enable the VFX by setting its draw function, and starting its timer.
 **
 ** @param vfx The VFX object to be modified.
 **/
void vfx_enable(VFX* vfx, vfx_draw_function* draw_function);

/** 
 ** @brief Disable the VFX by resetting its draw function, timer, and auxillary
 ** information.
 **
 ** @param vfx The VFX object to be modified.
 **/
void vfx_disable(VFX* vfx);

/** 
 ** @brief Draw 1 frame of the VFX, and decrement its timer. If the timer
 ** has reached 0 then call its clear function and disable the VFX.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_frame(VFX* vfx);

/**
 ** @brief Draw colored border of the board_window, avoiding the score along
 ** the bottom. 
 **
 ** @param vfx The VFX object to be modified.
 ** @param color_pair The color pair that will be used for the border. 
 **/
void draw_vfx_board_window_border(VFX* vfx, int16_t color_pair);

/**
 ** @brief Check whether a piece has been locked in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_lock_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function corresponding 
 ** to the shape of the locked piece.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_lock_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the color of the window border.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_lock_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the I piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_i_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the J piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_j_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the L piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_l_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the O piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_o_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the S piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_s_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the T piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_t_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the Z piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_lock_z_piece(VFX* vfx);

/**
 ** @brief Check whether a line clear occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_line_clear(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function corresponding 
 ** to the type of line clear.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_line_clear(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the color of the window border.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_line_clear(VFX* vfx);

/**
 ** @brief Color the window border the green.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_single(VFX* vfx); 

/**
 ** @brief Color the window border the blue.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_double(VFX* vfx); 

/**
 ** @brief Color the window border the yellow.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_triple(VFX* vfx); 

/**
 ** @brief Color the window border the cyan.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_tetris(VFX* vfx); 

/**
 ** @brief Color the window border the purple.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_t_spin(VFX* vfx); 

/**
 ** @brief Color the window border a rainbow effect.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_line_clear_all_clear(VFX* vfx); 

/**
 ** @brief Check whether a piece has been held in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_hold_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function corresponding 
 ** to the shape of the held piece.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_hold_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the color of the window border.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_hold_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the I piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_i_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the J piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_j_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the L piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_l_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the O piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_o_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the S piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_s_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the T piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_t_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the Z piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_hold_z_piece(VFX* vfx);

/**
 ** @brief Check whether a next piece has been loaded in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_next_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function corresponding 
 ** to the shape of the next piece.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_next_piece(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the color of the window border.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_next_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the I piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_i_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the J piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_j_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the L piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_l_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the O piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_o_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the S piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_s_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the T piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_t_piece(VFX* vfx);

/**
 ** @brief Color the window border the same color as the Z piece.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_next_z_piece(VFX* vfx);

/**
 ** @brief Check whether a point scoring action has occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_action(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, register the draw function and text 
 ** corresponding to the type of action, and store the y-coordinate of where
 ** it should be drawn according to other action info VFX.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_action(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the VFX text from the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_action(VFX* vfx);

/**
 ** @brief Print the action in red.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_single(VFX* vfx);

/**
 ** @brief Print the action in blue.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_double(VFX* vfx);

/**
 ** @brief Print the action in yellow.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_triple(VFX* vfx);

/**
 ** @brief Print the action in cyan.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_tetris(VFX* vfx);

/**
 ** @brief Print the action in purple.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_t_spin(VFX* vfx);

/**
 ** @brief Print the action in rainbow colors.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_action_all_clear(VFX* vfx);

/**
 ** @brief Check whether a combo occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_combo(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, register the draw function and text 
 ** corresponding to the combo, and store the y-coordinate of where it should 
 ** be drawn according to other action info VFX.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_combo(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the VFX text from the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_combo(VFX* vfx);

/**
 ** @brief Print the combo in red.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_combo(VFX* vfx);

/**
 ** @brief Check whether a back-to-back difficult clear combo occurred in this 
 ** frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_b2b_combo(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, register the draw function and text 
 ** corresponding to the back-to-back difficult clear combo, and store the 
 ** y-coordinate of where it should be drawn according to other action info VFX.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_b2b_combo(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the VFX text from the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_b2b_combo(VFX* vfx);

/**
 ** @brief Print the back-to-back difficult clear combo in orange.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_b2b_combo(VFX* vfx);

/**
 ** @brief Check whether a point scoring action has occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_points(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, register the draw function and text 
 ** corresponding to the number of points of the action, and store the 
 ** y-coordinate to be the bottom of the window.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_points(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the VFX text from the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_points(VFX* vfx);

/**
 ** @brief Print the number of points.
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_points(VFX* vfx);

/**
 ** @brief Check whether a level up occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_level_up(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, register the draw function and text 
 ** corresponding to the current level, and store the location it should be
 ** drawn.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_level_up(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the VFX text from the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_level_up(VFX* vfx);

/**
 ** @brief Print level up text in rainbow colors. 
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_level_up(VFX* vfx);

/**
 ** @brief Check whether the number of lines has changed in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_stats_lines(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function highlighting
 ** the stats window lines number.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_stats_lines(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the highlight from text in the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_stats_lines(VFX* vfx);

/**
 ** @brief Highlight text indicating number of lines cleared. 
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_stats_lines(VFX* vfx);

/**
 ** @brief Check whether a level up occurred in this frame.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from. 
 ** 
 ** @return True if condition met, otherwise False.
 **/
bool vfx_check_stats_level(VFX* vfx, const GameState* game_state);

/**
 ** @brief Enable the VFX object, and register the draw function highlighting
 ** the stats window level number.
 **
 ** @param vfx The VFX object to be modified.
 ** @param game_state The GameState object to be read from.
 **/
void vfx_enable_stats_level(VFX* vfx, const GameState* game_state);

/**
 ** @brief Clear the highlight from text in the window.
 **
 ** @param vfx The VFX object to be modified.
 **/
void clear_vfx_stats_level(VFX* vfx);

/**
 ** @brief Highlight text indicating the current level. 
 **
 ** @param vfx The VFX object to be modified.
 **/
void draw_vfx_stats_level(VFX* vfx);

#endif
