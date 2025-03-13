#ifndef VFX_H
#define VFX_H
#include "game_state.h"
#include "draw.h"

#define NUM_VFX 11
#define VFX_TEXT_MAX 64


extern const uint16_t LOCK_PIECE_VFX_FRAMES;
extern const uint16_t LINE_CLEAR_VFX_FRAMES;
extern const uint16_t HOLD_PIECE_VFX_FRAMES;
extern const uint16_t NEXT_PIECE_VFX_FRAMES;

extern const uint16_t ACTION_VFX_FRAMES;
extern const uint16_t COMBO_VFX_FRAMES;
extern const uint16_t B2B_COMBO_VFX_FRAMES;
extern const uint16_t SCORE_VFX_FRAMES;

extern const uint16_t LEVEL_UP_VFX_FRAMES;
extern const uint16_t STATS_LINES_VFX_FRAMES;
extern const uint16_t STATS_LEVEL_VFX_FRAMES;

extern const uint16_t LAST_ACTION_VFX_DIM_FRAMES;
extern const uint16_t LEVEL_UP_VFX_DIM_FRAMES;

struct VFX;

typedef struct VFX VFX;

typedef void draw_vfx_function(VFX* vfx);

struct VFX {
    GameWindow* game_window;
    draw_vfx_function* draw_function;
    draw_vfx_function* reset_function;
    uint16_t frame_timer;
    uint16_t frame_duration;
    bool enabled;
    int8_t y;
    int8_t x;
    char text[VFX_TEXT_MAX];
};

VFX vfx_get(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration);

VFX* vfx_init(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration);

void vfx_destroy(VFX* vfx);

void vfx_enable(VFX* vfx, draw_vfx_function* draw_function);

void vfx_disable(VFX* vfx);

void draw_vfx_frame(VFX* vfx);

void draw_vfx_board_window_border(VFX* vfx, int16_t color_pair);

void vfx_enable_lock_piece(VFX* vfx, GameState* game_state);

void draw_vfx_lock_piece_reset(VFX* vfx);

void draw_vfx_lock_i_piece(VFX* vfx);

void draw_vfx_lock_j_piece(VFX* vfx);

void draw_vfx_lock_l_piece(VFX* vfx);

void draw_vfx_lock_o_piece(VFX* vfx);

void draw_vfx_lock_s_piece(VFX* vfx);

void draw_vfx_lock_t_piece(VFX* vfx);

void draw_vfx_lock_z_piece(VFX* vfx);

void vfx_enable_line_clear(VFX* vfx, GameState* game_state);

void draw_vfx_line_clear_reset(VFX* vfx);

void draw_vfx_line_clear_single(VFX* vfx); 

void draw_vfx_line_clear_double(VFX* vfx); 

void draw_vfx_line_clear_triple(VFX* vfx); 

void draw_vfx_line_clear_tetris(VFX* vfx); 

void draw_vfx_line_clear_t_spin(VFX* vfx); 

void draw_vfx_line_clear_all_clear(VFX* vfx); 

void vfx_enable_hold_piece(VFX* vfx, GameState* game_state);

void draw_vfx_hold_piece_reset(VFX* vfx);

void draw_vfx_hold_i_piece(VFX* vfx);

void draw_vfx_hold_j_piece(VFX* vfx);

void draw_vfx_hold_l_piece(VFX* vfx);

void draw_vfx_hold_o_piece(VFX* vfx);

void draw_vfx_hold_s_piece(VFX* vfx);

void draw_vfx_hold_t_piece(VFX* vfx);

void draw_vfx_hold_z_piece(VFX* vfx);

void vfx_enable_next_piece(VFX* vfx, GameState* game_state);

void draw_vfx_next_piece_reset(VFX* vfx);

void draw_vfx_next_i_piece(VFX* vfx);

void draw_vfx_next_j_piece(VFX* vfx);

void draw_vfx_next_l_piece(VFX* vfx);

void draw_vfx_next_o_piece(VFX* vfx);

void draw_vfx_next_s_piece(VFX* vfx);

void draw_vfx_next_t_piece(VFX* vfx);

void draw_vfx_next_z_piece(VFX* vfx);

void vfx_enable_last_action(VFX* vfx_action, VFX* vfx_combo, VFX* vfx_b2b, VFX* vfx_score, GameState* game_state);

void draw_vfx_action_reset(VFX* vfx);

void draw_vfx_action_single(VFX* vfx);

void draw_vfx_action_double(VFX* vfx);

void draw_vfx_action_triple(VFX* vfx);

void draw_vfx_action_tetris(VFX* vfx);

void draw_vfx_action_t_spin(VFX* vfx);

void draw_vfx_action_all_clear(VFX* vfx);

void draw_vfx_combo_reset(VFX* vfx);

void draw_vfx_combo(VFX* vfx);

void draw_vfx_b2b_combo_reset(VFX* vfx);

void draw_vfx_b2b(VFX* vfx);

void draw_vfx_score_reset(VFX* vfx);

void draw_vfx_score(VFX* vfx);

void vfx_enable_level_up(VFX* vfx, GameState* game_state);

void draw_vfx_level_up_reset(VFX* vfx);

void draw_vfx_level_up(VFX* vfx);

void vfx_enable_stats_lines(VFX* vfx, GameState* game_state);

void draw_vfx_stats_lines_reset(VFX* vfx);

void draw_vfx_stats_lines(VFX* vfx);

void vfx_enable_stats_level(VFX* vfx, GameState* game_state);

void draw_vfx_stats_level_reset(VFX* vfx);

void draw_vfx_stats_level(VFX* vfx);

#endif
