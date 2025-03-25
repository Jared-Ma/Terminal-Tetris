#ifndef VFX_H
#define VFX_H
#include "draw.h"
#include "game_state.h"

#include <stdbool.h>
#include <stdint.h>

#define NUM_VFX 11
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

struct VFX;

typedef struct VFX VFX;

typedef void vfx_draw_function(VFX* vfx);

typedef bool vfx_cond_function(VFX* vfx, const GameState* game_state);

typedef void vfx_enable_function(VFX* vfx, const GameState* game_state);

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

VFX vfx_get(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
);

VFX* vfx_init(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
);

void vfx_destroy(VFX* vfx);

void vfx_enable(VFX* vfx, vfx_draw_function* draw_function);

void vfx_disable(VFX* vfx);

void draw_vfx_frame(VFX* vfx);

void draw_vfx_board_window_border(VFX* vfx, int16_t color_pair);

bool vfx_check_lock_piece(VFX* vfx, const GameState* game_state);

void vfx_enable_lock_piece(VFX* vfx, const GameState* game_state);

void clear_vfx_lock_piece(VFX* vfx);

void draw_vfx_lock_i_piece(VFX* vfx);

void draw_vfx_lock_j_piece(VFX* vfx);

void draw_vfx_lock_l_piece(VFX* vfx);

void draw_vfx_lock_o_piece(VFX* vfx);

void draw_vfx_lock_s_piece(VFX* vfx);

void draw_vfx_lock_t_piece(VFX* vfx);

void draw_vfx_lock_z_piece(VFX* vfx);

bool vfx_check_line_clear(VFX* vfx, const GameState* game_state);

void vfx_enable_line_clear(VFX* vfx, const GameState* game_state);

void clear_vfx_line_clear(VFX* vfx);

void draw_vfx_line_clear_single(VFX* vfx); 

void draw_vfx_line_clear_double(VFX* vfx); 

void draw_vfx_line_clear_triple(VFX* vfx); 

void draw_vfx_line_clear_tetris(VFX* vfx); 

void draw_vfx_line_clear_t_spin(VFX* vfx); 

void draw_vfx_line_clear_all_clear(VFX* vfx); 

bool vfx_check_hold_piece(VFX* vfx, const GameState* game_state);

void vfx_enable_hold_piece(VFX* vfx, const GameState* game_state);

void clear_vfx_hold_piece(VFX* vfx);

void draw_vfx_hold_i_piece(VFX* vfx);

void draw_vfx_hold_j_piece(VFX* vfx);

void draw_vfx_hold_l_piece(VFX* vfx);

void draw_vfx_hold_o_piece(VFX* vfx);

void draw_vfx_hold_s_piece(VFX* vfx);

void draw_vfx_hold_t_piece(VFX* vfx);

void draw_vfx_hold_z_piece(VFX* vfx);

bool vfx_check_next_piece(VFX* vfx, const GameState* game_state);

void vfx_enable_next_piece(VFX* vfx, const GameState* game_state);

void clear_vfx_next_piece(VFX* vfx);

void draw_vfx_next_i_piece(VFX* vfx);

void draw_vfx_next_j_piece(VFX* vfx);

void draw_vfx_next_l_piece(VFX* vfx);

void draw_vfx_next_o_piece(VFX* vfx);

void draw_vfx_next_s_piece(VFX* vfx);

void draw_vfx_next_t_piece(VFX* vfx);

void draw_vfx_next_z_piece(VFX* vfx);

bool vfx_check_action(VFX* vfx, const GameState* game_state);

void vfx_enable_action(VFX* vfx, const GameState* game_state);

void clear_vfx_action(VFX* vfx);

void draw_vfx_action_single(VFX* vfx);

void draw_vfx_action_double(VFX* vfx);

void draw_vfx_action_triple(VFX* vfx);

void draw_vfx_action_tetris(VFX* vfx);

void draw_vfx_action_t_spin(VFX* vfx);

void draw_vfx_action_all_clear(VFX* vfx);

bool vfx_check_combo(VFX* vfx, const GameState* game_state);

void vfx_enable_combo(VFX* vfx, const GameState* game_state);

void clear_vfx_combo(VFX* vfx);

void draw_vfx_combo(VFX* vfx);

bool vfx_check_b2b_combo(VFX* vfx, const GameState* game_state);

void vfx_enable_b2b_combo(VFX* vfx, const GameState* game_state);

void clear_vfx_b2b_combo(VFX* vfx);

void draw_vfx_b2b_combo(VFX* vfx);

bool vfx_check_points(VFX* vfx, const GameState* game_state);

void vfx_enable_points(VFX* vfx, const GameState* game_state);

void clear_vfx_points(VFX* vfx);

void draw_vfx_points(VFX* vfx);

bool vfx_check_level_up(VFX* vfx, const GameState* game_state);

void vfx_enable_level_up(VFX* vfx, const GameState* game_state);

void clear_vfx_level_up(VFX* vfx);

void draw_vfx_level_up(VFX* vfx);

bool vfx_check_stats_lines(VFX* vfx, const GameState* game_state);

void vfx_enable_stats_lines(VFX* vfx, const GameState* game_state);

void clear_vfx_stats_lines(VFX* vfx);

void draw_vfx_stats_lines(VFX* vfx);

bool vfx_check_stats_level(VFX* vfx, const GameState* game_state);

void vfx_enable_stats_level(VFX* vfx, const GameState* game_state);

void clear_vfx_stats_level(VFX* vfx);

void draw_vfx_stats_level(VFX* vfx);

#endif
