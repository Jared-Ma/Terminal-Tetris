#include "test_vfx.h"
#include "vfx.h"
#include "draw.h"

#include "assert_trace.h"

#include <stdbool.h>
#include <string.h>


bool test_vfx_get(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx = vfx_get(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    ASSERT(vfx.game_window == &board_window);
    ASSERT(vfx.draw_vfx == NULL);
    ASSERT(vfx.clear_vfx == clear_vfx_lock_piece);
    ASSERT(vfx.check_cond == vfx_check_lock_piece);
    ASSERT(vfx.enable_vfx == vfx_enable_lock_piece);
    ASSERT(vfx.frame_timer == 0);
    ASSERT(vfx.frame_duration == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx.enabled == false);
    ASSERT(vfx.y == 0);
    ASSERT(vfx.x == 0);
    ASSERT(strlen(vfx.text) == 0);
    return true;
}

bool test_vfx_init(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX* vfx = vfx_init(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    ASSERT(vfx->game_window == &board_window);
    ASSERT(vfx->draw_vfx == NULL);
    ASSERT(vfx->clear_vfx == clear_vfx_lock_piece);
    ASSERT(vfx->check_cond == vfx_check_lock_piece);
    ASSERT(vfx->enable_vfx == vfx_enable_lock_piece);
    ASSERT(vfx->frame_timer == 0);
    ASSERT(vfx->frame_duration == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx->enabled == false);
    ASSERT(vfx->y == 0);
    ASSERT(vfx->x == 0);
    ASSERT(strlen(vfx->text) == 0);
    vfx_destroy(vfx);
    return true;
}

bool test_vfx_enable(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx = vfx_get(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    vfx_enable(&vfx, draw_vfx_lock_i_piece);
    ASSERT(vfx.draw_vfx == draw_vfx_lock_i_piece);
    ASSERT(vfx.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx.enabled == true);
    return true;
}

bool test_vfx_disable(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx = vfx_get(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    vfx_enable(&vfx, draw_vfx_lock_i_piece);
    vfx_disable(&vfx);
    ASSERT(vfx.draw_vfx == NULL);
    ASSERT(vfx.frame_timer == 0);
    ASSERT(vfx.enabled == false);
    ASSERT(vfx.y == 0);
    ASSERT(vfx.x == 0);
    ASSERT(strlen(vfx.text) == 0);
    return true;
}

bool test_vfx_check_lock_piece(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_lock_piece = vfx_get(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    ASSERT(vfx_check_lock_piece(&vfx_lock_piece, &game_state) == false);
    game_state.last_locked_piece_shape = I;
    ASSERT(vfx_check_lock_piece(&vfx_lock_piece, &game_state) == true);
    return true;
}

bool test_vfx_enable_lock_piece(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_lock_piece = vfx_get(
        &board_window, 
        clear_vfx_lock_piece, 
        vfx_check_lock_piece, 
        vfx_enable_lock_piece, 
        LOCK_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == NULL);
    ASSERT(vfx_lock_piece.frame_timer == 0);
    ASSERT(vfx_lock_piece.enabled == false);

    game_state.last_locked_piece_shape = I;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_i_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = J;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_j_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = L;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_l_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = O;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_o_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = S;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_s_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = T;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_t_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    game_state.last_locked_piece_shape = Z;
    if (vfx_check_lock_piece(&vfx_lock_piece, &game_state)) vfx_enable_lock_piece(&vfx_lock_piece, &game_state);
    ASSERT(vfx_lock_piece.draw_vfx == draw_vfx_lock_z_piece);
    ASSERT(vfx_lock_piece.frame_timer == LOCK_PIECE_VFX_FRAMES);
    ASSERT(vfx_lock_piece.enabled == true);

    return true;
}

bool test_vfx_check_line_clear(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_line_clear = vfx_get(
        &board_window, 
        clear_vfx_line_clear, 
        vfx_check_line_clear, 
        vfx_enable_line_clear, 
        LINE_CLEAR_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_line_clear(&vfx_line_clear, &game_state) == false);
    game_state.last_action_num_lines = 1;
    ASSERT(vfx_check_line_clear(&vfx_line_clear, &game_state) == true);
    return true;
}

bool test_vfx_enable_line_clear(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_line_clear = vfx_get(
        &board_window, 
        clear_vfx_line_clear, 
        vfx_check_line_clear, 
        vfx_enable_line_clear, 
        LINE_CLEAR_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == NULL);
    ASSERT(vfx_line_clear.frame_timer == 0);
    ASSERT(vfx_line_clear.enabled == false);

    game_state.last_action_t_spin = true;
    game_state.last_action_t_spin_mini = false;
    game_state.last_action_num_lines = 1;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_t_spin);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = true;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_t_spin);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = false;
    game_state.last_action_all_clear = true;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_all_clear);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_all_clear = false;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_single);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_num_lines = 2;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_double);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_num_lines = 3;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_triple);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    game_state.last_action_num_lines = 4;
    if (vfx_check_line_clear(&vfx_line_clear, &game_state)) vfx_enable_line_clear(&vfx_line_clear, &game_state);
    ASSERT(vfx_line_clear.draw_vfx == draw_vfx_line_clear_tetris);
    ASSERT(vfx_line_clear.frame_timer == LINE_CLEAR_VFX_FRAMES);
    ASSERT(vfx_line_clear.enabled == true);

    return true;
}

bool test_vfx_check_hold_piece(void) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y, HOLD_WINDOW_X
    );
    VFX vfx_hold_piece = vfx_get(
        &hold_window, 
        clear_vfx_hold_piece, 
        vfx_check_hold_piece, 
        vfx_enable_hold_piece, 
        HOLD_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_hold_piece(&vfx_hold_piece, &game_state) == false);
    game_state.hold_piece_event_flag = true;
    ASSERT(vfx_check_hold_piece(&vfx_hold_piece, &game_state) == true);
    return true;
}

bool test_vfx_enable_hold_piece(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_hold_piece = vfx_get(
        &board_window, 
        clear_vfx_hold_piece, 
        vfx_check_hold_piece, 
        vfx_enable_hold_piece, 
        HOLD_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == NULL);
    ASSERT(vfx_hold_piece.frame_timer == 0);
    ASSERT(vfx_hold_piece.enabled == false);

    game_state.hold_piece_event_flag = true;
    game_state.hold_piece.shape = I;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_i_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = J;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_j_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = L;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_l_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = O;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_o_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = S;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_s_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = T;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_t_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    game_state.hold_piece.shape = Z;
    if (vfx_check_hold_piece(&vfx_hold_piece, &game_state)) vfx_enable_hold_piece(&vfx_hold_piece, &game_state);
    ASSERT(vfx_hold_piece.draw_vfx == draw_vfx_hold_z_piece);
    ASSERT(vfx_hold_piece.frame_timer == HOLD_PIECE_VFX_FRAMES);
    ASSERT(vfx_hold_piece.enabled == true);

    return true;
}

bool test_vfx_check_next_piece(void) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y, NEXT_WINDOW_X
    );
    VFX vfx_next_piece = vfx_get(
        &next_window, 
        clear_vfx_next_piece, 
        vfx_check_next_piece, 
        vfx_enable_next_piece, 
        NEXT_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_next_piece(&vfx_next_piece, &game_state) == false);
    game_state.next_piece_event_flag = true;
    ASSERT(vfx_check_next_piece(&vfx_next_piece, &game_state) == true);
    return true;
}

bool test_vfx_enable_next_piece(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_next_piece = vfx_get(
        &board_window, 
        clear_vfx_next_piece, 
        vfx_check_next_piece, 
        vfx_enable_next_piece, 
        NEXT_PIECE_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == NULL);
    ASSERT(vfx_next_piece.frame_timer == 0);
    ASSERT(vfx_next_piece.enabled == false);

    game_state.next_piece_event_flag = true;
    game_state.next_piece.shape = I;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_i_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = J;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_j_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = L;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_l_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = O;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_o_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = S;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_s_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = T;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_t_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    game_state.next_piece.shape = Z;
    if (vfx_check_next_piece(&vfx_next_piece, &game_state)) vfx_enable_next_piece(&vfx_next_piece, &game_state);
    ASSERT(vfx_next_piece.draw_vfx == draw_vfx_next_z_piece);
    ASSERT(vfx_next_piece.frame_timer == NEXT_PIECE_VFX_FRAMES);
    ASSERT(vfx_next_piece.enabled == true);

    return true;
}

bool test_vfx_check_action(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_action = vfx_get(
        &stats_window, 
        clear_vfx_action, 
        vfx_check_action, 
        vfx_enable_action, 
        ACTION_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_action(&vfx_action, &game_state) == false);
    game_state.last_action_num_lines = 1;
    ASSERT(vfx_check_action(&vfx_action, &game_state) == true);

    game_state.last_action_num_lines = 0;
    game_state.last_action_t_spin = true;
    ASSERT(vfx_check_action(&vfx_action, &game_state) == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = true;
    ASSERT(vfx_check_action(&vfx_action, &game_state) == true);
    return true;
}

bool test_vfx_enable_action_line_clear(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_action = vfx_get(
        &stats_window, 
        clear_vfx_action, 
        vfx_check_action, 
        vfx_enable_action, 
        ACTION_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strlen(vfx_action.text) == 0);
    ASSERT(vfx_action.y == 0);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == NULL);
    ASSERT(vfx_action.frame_timer == 0);
    ASSERT(vfx_action.enabled == false);

    game_state.last_action_num_lines = 1;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "single") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_single);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 2;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "double") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_double);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 3;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "triple") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_triple);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 4;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "tetris") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_tetris);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    return true;
}

bool test_vfx_enable_action_t_spin(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_action = vfx_get(
        &stats_window, 
        clear_vfx_action, 
        vfx_check_action, 
        vfx_enable_action, 
        ACTION_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strlen(vfx_action.text) == 0);
    ASSERT(vfx_action.y == 0);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == NULL);
    ASSERT(vfx_action.frame_timer == 0);
    ASSERT(vfx_action.enabled == false);

    game_state.last_action_t_spin = true;
    game_state.last_action_num_lines = 0;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 1;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin\nsingle") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 2;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin\ndouble") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 3;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin\ntriple") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    return true;
}

bool test_vfx_enable_action_t_spin_mini(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_action = vfx_get(
        &stats_window, 
        clear_vfx_action, 
        vfx_check_action, 
        vfx_enable_action, 
        ACTION_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strlen(vfx_action.text) == 0);
    ASSERT(vfx_action.y == 0);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == NULL);
    ASSERT(vfx_action.frame_timer == 0);
    ASSERT(vfx_action.enabled == false);

    game_state.last_action_t_spin_mini = true;
    game_state.last_action_num_lines = 0;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin mini") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 1);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 1;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin mini\nsingle") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 2;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "t-spin mini\ndouble") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_t_spin);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    return true;
}

bool test_vfx_enable_action_all_clear(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_action = vfx_get(
        &stats_window, 
        clear_vfx_action, 
        vfx_check_action, 
        vfx_enable_action, 
        ACTION_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strlen(vfx_action.text) == 0);
    ASSERT(vfx_action.y == 0);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == NULL);
    ASSERT(vfx_action.frame_timer == 0);
    ASSERT(vfx_action.enabled == false);

    game_state.last_action_all_clear = true;
    game_state.last_action_num_lines = 1;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "single\nall clear") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_all_clear);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 2;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "double\nall clear") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_all_clear);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 3;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "triple\nall clear") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_all_clear);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 4;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "tetris\nall clear") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_all_clear);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    game_state.last_action_num_lines = 4;
    game_state.tetris_all_clear_combo = 1;
    if (vfx_check_action(&vfx_action, &game_state)) vfx_enable_action(&vfx_action, &game_state);
    ASSERT(strcmp(vfx_action.text, "b2b tetris\nall clear") == 0);
    ASSERT(vfx_action.y == vfx_action.game_window->content_h - 2);
    ASSERT(vfx_action.x == 0);
    ASSERT(vfx_action.draw_vfx == draw_vfx_action_all_clear);
    ASSERT(vfx_action.frame_timer == ACTION_VFX_FRAMES);
    ASSERT(vfx_action.enabled == true);

    return true;
}

bool test_vfx_check_combo(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_combo = vfx_get(
        &stats_window, 
        clear_vfx_combo, 
        vfx_check_combo, 
        vfx_enable_combo, 
        COMBO_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_combo(&vfx_combo, &game_state) == false);
    game_state.last_action_num_lines = 1;
    game_state.combo = 1;
    ASSERT(vfx_check_combo(&vfx_combo, &game_state) == true);

    game_state.last_action_num_lines = 0;
    game_state.last_action_t_spin = true;
    ASSERT(vfx_check_combo(&vfx_combo, &game_state) == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = true;
    ASSERT(vfx_check_combo(&vfx_combo, &game_state) == true);
    return true;
}

bool test_vfx_enable_combo(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_combo = vfx_get(
        &stats_window, 
        clear_vfx_combo, 
        vfx_check_combo, 
        vfx_enable_combo, 
        COMBO_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_combo(&vfx_combo, &game_state)) vfx_enable_combo(&vfx_combo, &game_state);
    ASSERT(strlen(vfx_combo.text) == 0);
    ASSERT(vfx_combo.y == 0);
    ASSERT(vfx_combo.x == 0);
    ASSERT(vfx_combo.draw_vfx == NULL);
    ASSERT(vfx_combo.frame_timer == 0);
    ASSERT(vfx_combo.enabled == false);

    game_state.last_action_num_lines = 1;
    game_state.combo = 1;
    if (vfx_check_combo(&vfx_combo, &game_state)) vfx_enable_combo(&vfx_combo, &game_state);
    ASSERT(strcmp(vfx_combo.text, "1 x combo") == 0);
    ASSERT(vfx_combo.y == vfx_combo.game_window->content_h - 1);
    ASSERT(vfx_combo.x == 0);
    ASSERT(vfx_combo.draw_vfx == draw_vfx_combo);
    ASSERT(vfx_combo.frame_timer == COMBO_VFX_FRAMES);
    ASSERT(vfx_combo.enabled == true);
    
    return true;
}

bool test_vfx_check_b2b_combo(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_b2b_combo = vfx_get(
        &stats_window, 
        clear_vfx_b2b_combo, 
        vfx_check_b2b_combo, 
        vfx_enable_b2b_combo, 
        COMBO_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_b2b_combo(&vfx_b2b_combo, &game_state) == false);
    game_state.last_action_num_lines = 1;
    game_state.difficult_clear_combo = 1;
    ASSERT(vfx_check_b2b_combo(&vfx_b2b_combo, &game_state) == true);

    game_state.last_action_num_lines = 0;
    game_state.last_action_t_spin = true;
    ASSERT(vfx_check_b2b_combo(&vfx_b2b_combo, &game_state) == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = true;
    ASSERT(vfx_check_b2b_combo(&vfx_b2b_combo, &game_state) == true);
    return true;
}

bool test_vfx_enable_b2b_combo(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_b2b_combo = vfx_get(
        &stats_window, 
        clear_vfx_b2b_combo, 
        vfx_check_b2b_combo, 
        vfx_enable_b2b_combo, 
        B2B_COMBO_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_b2b_combo(&vfx_b2b_combo, &game_state)) vfx_enable_b2b_combo(&vfx_b2b_combo, &game_state);
    ASSERT(strlen(vfx_b2b_combo.text) == 0);
    ASSERT(vfx_b2b_combo.y == 0);
    ASSERT(vfx_b2b_combo.x == 0);
    ASSERT(vfx_b2b_combo.draw_vfx == NULL);
    ASSERT(vfx_b2b_combo.frame_timer == 0);
    ASSERT(vfx_b2b_combo.enabled == false);

    game_state.last_action_num_lines = 1;
    game_state.difficult_clear_combo = 1;
    if (vfx_check_b2b_combo(&vfx_b2b_combo, &game_state)) vfx_enable_b2b_combo(&vfx_b2b_combo, &game_state);
    ASSERT(strcmp(vfx_b2b_combo.text, "1 x b2b") == 0);
    ASSERT(vfx_b2b_combo.y == vfx_b2b_combo.game_window->content_h - 1);
    ASSERT(vfx_b2b_combo.x == 0);
    ASSERT(vfx_b2b_combo.draw_vfx == draw_vfx_b2b_combo);
    ASSERT(vfx_b2b_combo.frame_timer == B2B_COMBO_VFX_FRAMES);
    ASSERT(vfx_b2b_combo.enabled == true);
    
    return true;
}

bool test_vfx_check_points(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_points = vfx_get(
        &stats_window, 
        clear_vfx_points, 
        vfx_check_points, 
        vfx_enable_points, 
        POINTS_VFX_FRAMES
    );
    GameState game_state = game_state_get();
    
    ASSERT(vfx_check_points(&vfx_points, &game_state) == false);
    game_state.last_action_num_lines = 1;
    game_state.last_action_points = 100;
    ASSERT(vfx_check_points(&vfx_points, &game_state) == true);

    game_state.last_action_num_lines = 0;
    game_state.last_action_t_spin = true;
    ASSERT(vfx_check_points(&vfx_points, &game_state) == true);

    game_state.last_action_t_spin = false;
    game_state.last_action_t_spin_mini = true;
    ASSERT(vfx_check_points(&vfx_points, &game_state) == true);
    return true;
}

bool test_vfx_enable_points(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_points = vfx_get(
        &stats_window, 
        clear_vfx_points, 
        vfx_check_points, 
        vfx_enable_points, 
        POINTS_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_points(&vfx_points, &game_state)) vfx_enable_points(&vfx_points, &game_state);
    ASSERT(strlen(vfx_points.text) == 0);
    ASSERT(vfx_points.y == 0);
    ASSERT(vfx_points.x == 0);
    ASSERT(vfx_points.draw_vfx == NULL);
    ASSERT(vfx_points.frame_timer == 0);
    ASSERT(vfx_points.enabled == false);

    game_state.last_action_num_lines = 1;
    game_state.last_action_points = 100;
    char points_text[VFX_TEXT_MAX];
    sprintf(points_text, "%*lu", vfx_points.game_window->content_w, game_state.last_action_points); 
    if (vfx_check_points(&vfx_points, &game_state)) vfx_enable_points(&vfx_points, &game_state);
    ASSERT(strcmp(vfx_points.text, points_text) == 0);
    ASSERT(vfx_points.y == vfx_points.game_window->content_h - 1);
    ASSERT(vfx_points.x == 0);
    ASSERT(vfx_points.draw_vfx == draw_vfx_points);
    ASSERT(vfx_points.frame_timer == POINTS_VFX_FRAMES);
    ASSERT(vfx_points.enabled == true);
    
    return true;
}

bool test_vfx_check_level_up(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_level_up = vfx_get(
        &board_window, 
        clear_vfx_level_up,
        vfx_check_level_up,
        vfx_enable_level_up,
        LEVEL_UP_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    ASSERT(vfx_check_level_up(&vfx_level_up, &game_state) == false);
    game_state.level_up_event_flag = 1;
    ASSERT(vfx_check_level_up(&vfx_level_up, &game_state) == true);
    return true;
}

bool test_vfx_enable_level_up(void) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    VFX vfx_level_up = vfx_get(
        &board_window, 
        clear_vfx_level_up,
        vfx_check_level_up,
        vfx_enable_level_up,
        LEVEL_UP_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_level_up(&vfx_level_up, &game_state)) vfx_enable_level_up(&vfx_level_up, &game_state);
    ASSERT(strlen(vfx_level_up.text) == 0);
    ASSERT(vfx_level_up.y == 0);
    ASSERT(vfx_level_up.x == 0);
    ASSERT(vfx_level_up.draw_vfx == NULL);
    ASSERT(vfx_level_up.frame_timer == 0);
    ASSERT(vfx_level_up.enabled == false);

    game_state.level_up_event_flag = 1;
    game_state.level = 2;
    char level_text[VFX_TEXT_MAX];
    sprintf(level_text, "LEVEL%*lu", (int)(LEVEL_UP_VFX_W - strlen("LEVEL")), game_state.level);
    if (vfx_check_level_up(&vfx_level_up, &game_state)) vfx_enable_level_up(&vfx_level_up, &game_state);
    ASSERT(strcmp(vfx_level_up.text, level_text) == 0);
    ASSERT(vfx_level_up.y == LEVEL_UP_VFX_Y);
    ASSERT(vfx_level_up.x == vfx_level_up.game_window->content_w/2 - strlen(vfx_level_up.text)/2);
    ASSERT(vfx_level_up.draw_vfx == draw_vfx_level_up);
    ASSERT(vfx_level_up.frame_timer == LEVEL_UP_VFX_FRAMES);
    ASSERT(vfx_level_up.enabled == true);

    game_state.level = 10;
    sprintf(level_text, "LEVEL%*lu", (int)(LEVEL_UP_VFX_W - strlen("LEVEL")), game_state.level);
    if (vfx_check_level_up(&vfx_level_up, &game_state)) vfx_enable_level_up(&vfx_level_up, &game_state);
    ASSERT(strcmp(vfx_level_up.text, level_text) == 0);
    ASSERT(vfx_level_up.y == LEVEL_UP_VFX_Y);
    ASSERT(vfx_level_up.x == vfx_level_up.game_window->content_w/2 - strlen(vfx_level_up.text)/2);
    ASSERT(vfx_level_up.draw_vfx == draw_vfx_level_up);
    ASSERT(vfx_level_up.frame_timer == LEVEL_UP_VFX_FRAMES);
    ASSERT(vfx_level_up.enabled == true);

    return true;
}

bool test_vfx_check_stats_lines(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_stats_lines = vfx_get(
        &stats_window, 
        clear_vfx_stats_lines,
        vfx_check_stats_lines,
        vfx_enable_stats_lines,
        STATS_LINES_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    ASSERT(vfx_check_stats_lines(&vfx_stats_lines, &game_state) == false);
    game_state.last_action_num_lines = 1;
    ASSERT(vfx_check_stats_lines(&vfx_stats_lines, &game_state) == true);
    return true;
}

bool test_vfx_enable_stats_lines(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, 
        STATS_WINDOW_W, 
        STATS_WINDOW_Y, 
        STATS_WINDOW_X
    );
    VFX vfx_stats_lines = vfx_get(
        &stats_window, 
        clear_vfx_stats_lines, 
        vfx_check_stats_lines, 
        vfx_enable_stats_lines, 
        STATS_LINES_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_stats_lines(&vfx_stats_lines, &game_state)) vfx_enable_stats_lines(&vfx_stats_lines, &game_state);
    ASSERT(strlen(vfx_stats_lines.text) == 0);
    ASSERT(vfx_stats_lines.y == 0);
    ASSERT(vfx_stats_lines.x == 0);
    ASSERT(vfx_stats_lines.draw_vfx == NULL);
    ASSERT(vfx_stats_lines.frame_timer == 0);
    ASSERT(vfx_stats_lines.enabled == false);

    game_state.last_action_num_lines = 1;
    game_state.lines = 1;
    char lines_text[VFX_TEXT_MAX];
    sprintf(lines_text, "lines: %lu", game_state.lines);
    if (vfx_check_stats_lines(&vfx_stats_lines, &game_state)) vfx_enable_stats_lines(&vfx_stats_lines, &game_state);
    ASSERT(strcmp(vfx_stats_lines.text, lines_text) == 0);
    ASSERT(vfx_stats_lines.y == STATS_LINES_Y);
    ASSERT(vfx_stats_lines.x == STATS_LINES_X);
    ASSERT(vfx_stats_lines.draw_vfx == draw_vfx_stats_lines);
    ASSERT(vfx_stats_lines.frame_timer == STATS_LINES_VFX_FRAMES);
    ASSERT(vfx_stats_lines.enabled == true);

    return true;
}

bool test_vfx_check_stats_level(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    VFX vfx_stats_level = vfx_get(
        &stats_window, 
        clear_vfx_stats_level,
        vfx_check_stats_level,
        vfx_enable_stats_level,
        STATS_LEVEL_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    ASSERT(vfx_check_stats_level(&vfx_stats_level, &game_state) == false);
    game_state.level_up_event_flag = 1;
    ASSERT(vfx_check_stats_level(&vfx_stats_level, &game_state) == true);
    return true;
}

bool test_vfx_enable_stats_level(void) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, 
        STATS_WINDOW_W, 
        STATS_WINDOW_Y, 
        STATS_WINDOW_X
    );
    VFX vfx_stats_level = vfx_get(
        &stats_window, 
        clear_vfx_stats_level, 
        vfx_check_stats_level, 
        vfx_enable_stats_level, 
        STATS_LEVEL_VFX_FRAMES
    );
    GameState game_state = game_state_get();

    if (vfx_check_stats_level(&vfx_stats_level, &game_state)) vfx_enable_stats_level(&vfx_stats_level, &game_state);
    ASSERT(strlen(vfx_stats_level.text) == 0);
    ASSERT(vfx_stats_level.y == 0);
    ASSERT(vfx_stats_level.x == 0);
    ASSERT(vfx_stats_level.draw_vfx == NULL);
    ASSERT(vfx_stats_level.frame_timer == 0);
    ASSERT(vfx_stats_level.enabled == false);

    game_state.level_up_event_flag = 1;
    game_state.level = 2;
    char level_text[VFX_TEXT_MAX];
    sprintf(level_text, "level: %lu", game_state.level);
    if (vfx_check_stats_level(&vfx_stats_level, &game_state)) vfx_enable_stats_level(&vfx_stats_level, &game_state);
    ASSERT(strcmp(vfx_stats_level.text, level_text) == 0);
    ASSERT(vfx_stats_level.y == STATS_LEVEL_Y);
    ASSERT(vfx_stats_level.x == STATS_LEVEL_X);
    ASSERT(vfx_stats_level.draw_vfx == draw_vfx_stats_level);
    ASSERT(vfx_stats_level.frame_timer == STATS_LEVEL_VFX_FRAMES);
    ASSERT(vfx_stats_level.enabled == true);

    return true;
}
