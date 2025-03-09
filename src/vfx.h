#ifndef VFX_H
#define VFX_H
#include "game_state.h"
#include "draw.h"

#define NUM_VFX 6


struct VFX;

typedef struct VFX VFX;

typedef void draw_vfx_function(VFX* vfx);

struct VFX {
    GameWindow* game_window;
    draw_vfx_function* draw_function;
    draw_vfx_function* reset_function;
    uint16_t frame_duration;
    uint16_t frame_timer;
    bool enabled;
    int8_t y;
    int8_t x;
    char text[128];
};

VFX vfx_get(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration);

VFX* vfx_init(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration);

void vfx_destroy(VFX* vfx);

void vfx_enable(VFX* vfx, draw_vfx_function* draw_function);

void vfx_enable_line_clear(VFX* vfx, GameState* game_state);

void vfx_enable_hold_piece(VFX* vfx, GameState* game_state);

void vfx_enable_last_action(
    VFX* vfx_last_action_type, 
    VFX* vfx_last_action_combo, 
    VFX* vfx_last_action_b2b, 
    VFX* vfx_last_action_score, 
    GameState* game_state
);

void vfx_disable(VFX* vfx);

void draw_vfx_frame(VFX* vfx);

void draw_vfx_line_clear_reset(VFX* vfx);

void draw_vfx_line_clear_single(VFX* vfx); 

void draw_vfx_line_clear_double(VFX* vfx); 

void draw_vfx_line_clear_triple(VFX* vfx); 

void draw_vfx_line_clear_tetris(VFX* vfx); 

void draw_vfx_line_clear_t_spin(VFX* vfx); 

void draw_vfx_line_clear_perfect(VFX* vfx); 

void draw_vfx_hold_piece_reset(VFX* vfx);

void draw_vfx_hold_i_piece(VFX* vfx);

void draw_vfx_hold_j_piece(VFX* vfx);

void draw_vfx_hold_l_piece(VFX* vfx);

void draw_vfx_hold_o_piece(VFX* vfx);

void draw_vfx_hold_s_piece(VFX* vfx);

void draw_vfx_hold_t_piece(VFX* vfx);

void draw_vfx_hold_z_piece(VFX* vfx);

void draw_vfx_last_action_type_reset(VFX* vfx);

void draw_vfx_last_action_single(VFX* vfx);

void draw_vfx_last_action_double(VFX* vfx);

void draw_vfx_last_action_triple(VFX* vfx);

void draw_vfx_last_action_tetris(VFX* vfx);

void draw_vfx_last_action_t_spin(VFX* vfx);

void draw_vfx_last_action_perfect_clear(VFX* vfx);

void draw_vfx_last_action_combo_reset(VFX* vfx);

void draw_vfx_last_action_combo(VFX* vfx);

void draw_vfx_last_action_b2b_reset(VFX* vfx);

void draw_vfx_last_action_b2b(VFX* vfx);

void draw_vfx_last_action_score_reset(VFX* vfx);

void draw_vfx_last_action_score(VFX* vfx);

#endif