#include "vfx.h"
#include "draw.h"
#include "game_state.h"
#include "logger.h"

#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const uint16_t HOLD_PIECE_VFX_FRAMES = 10;
const uint16_t NEXT_PIECE_VFX_FRAMES = 10;
const uint16_t LOCK_PIECE_VFX_FRAMES = 10;
const uint16_t LINE_CLEAR_VFX_FRAMES = 30;

const uint16_t ACTION_VFX_FRAMES    = 240;
const uint16_t COMBO_VFX_FRAMES     = 240;
const uint16_t B2B_COMBO_VFX_FRAMES = 240;
const uint16_t POINTS_VFX_FRAMES     = 240;

const uint16_t LEVEL_UP_VFX_FRAMES    = 120;
const uint16_t STATS_LINES_VFX_FRAMES = 5;
const uint16_t STATS_LEVEL_VFX_FRAMES = 5;

const uint16_t LAST_ACTION_VFX_DIM_FRAMES = 30;
const uint16_t LEVEL_UP_VFX_DIM_FRAMES    = 30;

const int8_t LEVEL_UP_VFX_Y = 5;
const int8_t LEVEL_UP_VFX_W = 8;

VFX vfx_get(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
) {
    VFX visual_effect = {
        .game_window = game_window,
        .draw_vfx = NULL,
        .clear_vfx = clear_function,
        .check_cond = cond_function,
        .enable_vfx = enable_function,
        .frame_timer = 0,
        .frame_duration = frame_duration,
        .enabled = false,
        .y = 0,
        .x = 0,
        .text = { 0 }
    };
    return visual_effect;
}

VFX* vfx_init(
    GameWindow* game_window, 
    vfx_draw_function* clear_function, 
    vfx_cond_function* cond_function, 
    vfx_enable_function* enable_function, 
    uint16_t frame_duration
) {
    VFX* vfx = malloc(sizeof(VFX));
    *vfx = vfx_get(game_window, clear_function, cond_function, enable_function, frame_duration);
    return vfx;
}

void vfx_destroy(VFX* vfx) {
    if (!vfx) {
        return;
    }
    *vfx = (VFX){ 0 };
    free(vfx);
}

void vfx_enable(VFX* vfx, vfx_draw_function* draw_function) {
    if (!vfx || !draw_function) {
        return;
    }
    vfx->draw_vfx = draw_function;
    vfx->frame_timer = vfx->frame_duration;
    vfx->enabled = true;
}

void vfx_disable(VFX* vfx) {
    if (!vfx) {
        return;
    }
    vfx->draw_vfx = NULL;
    vfx->frame_timer = 0;
    vfx->enabled = false;
    vfx->y = 0;
    vfx->x = 0;
    memset(vfx->text, 0, sizeof(vfx->text));
}

void draw_vfx_frame(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->enabled) {
        if (vfx->frame_timer > 0) {
            vfx->draw_vfx(vfx);
            vfx->frame_timer--;
        } else {
            vfx->clear_vfx(vfx);
            vfx_disable(vfx);
        }
    }
}

void draw_vfx_board_window_border(VFX* vfx, int16_t color_pair) {
    if (!vfx) {
        return;
    }

    wattron(vfx->game_window->border, COLOR_PAIR(color_pair));

    // draw corners of border
    mvwaddch(vfx->game_window->border, 0, 0, ACS_ULCORNER);
    mvwaddch(vfx->game_window->border, 0, vfx->game_window->border_w - 1, ACS_URCORNER);
    mvwaddch(vfx->game_window->border, vfx->game_window->border_h - 1, 0, ACS_LLCORNER);
    mvwaddch(vfx->game_window->border, vfx->game_window->border_h - 1, vfx->game_window->border_w - 1, ACS_LRCORNER);
    
    // draw top, left, and right sides of border
    mvwhline(vfx->game_window->border, 0, 1, ACS_HLINE, vfx->game_window->border_w - 2);
    mvwvline(vfx->game_window->border, 1, 0, ACS_VLINE, vfx->game_window->border_h - 2);
    mvwvline(vfx->game_window->border, 1, vfx->game_window->border_w - 1, ACS_VLINE, vfx->game_window->border_h - 2);
    
    // draw bottom side of border without overwriting score
    mvwhline(vfx->game_window->border, vfx->game_window->border_h - 1, 1, ACS_HLINE, vfx->game_window->border_w/2 - 5);
    mvwhline(vfx->game_window->border, vfx->game_window->border_h - 1, vfx->game_window->border_w/2 + 4, ACS_HLINE, vfx->game_window->border_w/2 - 5);
    
    wattroff(vfx->game_window->border, COLOR_PAIR(color_pair));
}

bool vfx_check_lock_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_locked_piece_shape > 0;
}

void vfx_enable_lock_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->last_locked_piece_shape == I) {
        vfx_enable(vfx, draw_vfx_lock_i_piece);
    } else if (game_state->last_locked_piece_shape == J) {
        vfx_enable(vfx, draw_vfx_lock_j_piece);
    } else if (game_state->last_locked_piece_shape == L) {
        vfx_enable(vfx, draw_vfx_lock_l_piece);
    } else if (game_state->last_locked_piece_shape == O) {
        vfx_enable(vfx, draw_vfx_lock_o_piece);
    } else if (game_state->last_locked_piece_shape == S) {
        vfx_enable(vfx, draw_vfx_lock_s_piece);
    } else if (game_state->last_locked_piece_shape == T) {
        vfx_enable(vfx, draw_vfx_lock_t_piece);
    } else if (game_state->last_locked_piece_shape == Z) {
        vfx_enable(vfx, draw_vfx_lock_z_piece);
    }
}

void clear_vfx_lock_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_DEFAULT);
}

void draw_vfx_lock_i_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_CYAN);
}

void draw_vfx_lock_j_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_BLUE);
}

void draw_vfx_lock_l_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_ORANGE);
}

void draw_vfx_lock_o_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_YELLOW);
}

void draw_vfx_lock_s_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_GREEN);
}

void draw_vfx_lock_t_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_MAGENTA);
}

void draw_vfx_lock_z_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_RED);
}

bool vfx_check_line_clear(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_num_lines > 0;
}

void vfx_enable_line_clear(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->last_action_t_spin || game_state->last_action_t_spin_mini) {
        vfx_enable(vfx, draw_vfx_line_clear_t_spin);
    } else if (game_state->last_action_all_clear) {
        vfx_enable(vfx, draw_vfx_line_clear_all_clear);
    } else if (game_state->last_action_num_lines == 1) {
        vfx_enable(vfx, draw_vfx_line_clear_single);
    } else if (game_state->last_action_num_lines == 2) {
        vfx_enable(vfx, draw_vfx_line_clear_double);
    } else if (game_state->last_action_num_lines == 3) {
        vfx_enable(vfx, draw_vfx_line_clear_triple);
    } else if (game_state->last_action_num_lines == 4) {
        vfx_enable(vfx, draw_vfx_line_clear_tetris);
    }
}

void clear_vfx_line_clear(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_DEFAULT);
}

void draw_vfx_line_clear_single(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_GREEN);
}

void draw_vfx_line_clear_double(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_BLUE);
}

void draw_vfx_line_clear_triple(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_YELLOW);
}

void draw_vfx_line_clear_tetris(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_CYAN);
}

void draw_vfx_line_clear_t_spin(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_vfx_board_window_border(vfx, COLOR_PAIR_MAGENTA);
}

void draw_vfx_line_clear_all_clear(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_RED);
    } else if ((vfx->frame_timer + 1) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_ORANGE);
    } else if ((vfx->frame_timer + 2) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_YELLOW);
    } else if ((vfx->frame_timer + 3) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_GREEN);
    } else if ((vfx->frame_timer + 4) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_CYAN);
    } else if ((vfx->frame_timer + 5) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_BLUE);
    } else if ((vfx->frame_timer + 6) % 7 == 0) {
        draw_vfx_board_window_border(vfx, COLOR_PAIR_MAGENTA);
    }
}

bool vfx_check_hold_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->hold_piece_event_flag;
}

void vfx_enable_hold_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->hold_piece.shape == I) {
        vfx_enable(vfx, draw_vfx_hold_i_piece);
    } else if (game_state->hold_piece.shape == J) {
        vfx_enable(vfx, draw_vfx_hold_j_piece);
    } else if (game_state->hold_piece.shape == L) {
        vfx_enable(vfx, draw_vfx_hold_l_piece);
    } else if (game_state->hold_piece.shape == O) {
        vfx_enable(vfx, draw_vfx_hold_o_piece);
    } else if (game_state->hold_piece.shape == S) {
        vfx_enable(vfx, draw_vfx_hold_s_piece);
    } else if (game_state->hold_piece.shape == T) {
        vfx_enable(vfx, draw_vfx_hold_t_piece);
    } else if (game_state->hold_piece.shape == Z) {
        vfx_enable(vfx, draw_vfx_hold_z_piece);
    }
}

void clear_vfx_hold_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_DEFAULT);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_DEFAULT);
}

void draw_vfx_hold_i_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_CYAN);
}

void draw_vfx_hold_j_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_BLUE);
}

void draw_vfx_hold_l_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_ORANGE);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_ORANGE);
}

void draw_vfx_hold_o_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_YELLOW);
}

void draw_vfx_hold_s_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_GREEN);
}

void draw_vfx_hold_t_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_MAGENTA);
}

void draw_vfx_hold_z_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_RED);
    draw_window_title(vfx->game_window, HOLD_TITLE, COLOR_PAIR_RED);
}

bool vfx_check_next_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->next_piece_event_flag;
}

void vfx_enable_next_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->next_piece.shape == I) {
        vfx_enable(vfx, draw_vfx_next_i_piece);
    } else if (game_state->next_piece.shape == J) {
        vfx_enable(vfx, draw_vfx_next_j_piece);
    } else if (game_state->next_piece.shape == L) {
        vfx_enable(vfx, draw_vfx_next_l_piece);
    } else if (game_state->next_piece.shape == O) {
        vfx_enable(vfx, draw_vfx_next_o_piece);
    } else if (game_state->next_piece.shape == S) {
        vfx_enable(vfx, draw_vfx_next_s_piece);
    } else if (game_state->next_piece.shape == T) {
        vfx_enable(vfx, draw_vfx_next_t_piece);
    } else if (game_state->next_piece.shape == Z) {
        vfx_enable(vfx, draw_vfx_next_z_piece);
    }
}

void clear_vfx_next_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_DEFAULT);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_DEFAULT);
}

void draw_vfx_next_i_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_CYAN);
}

void draw_vfx_next_j_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_BLUE);
}

void draw_vfx_next_l_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_ORANGE);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_ORANGE);
}

void draw_vfx_next_o_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_YELLOW);
}

void draw_vfx_next_s_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_GREEN);
}

void draw_vfx_next_t_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_MAGENTA);
}

void draw_vfx_next_z_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_RED);
    draw_window_title(vfx->game_window, NEXT_TITLE, COLOR_PAIR_RED);
}

bool vfx_check_action(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0;
}

void vfx_enable_action(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    vfx_disable(vfx);
    vfx->y = vfx->game_window->content_h;
    vfx->y -= (game_state->last_action_points > 0) ? 1 : 0;
    vfx->y -= (game_state->difficult_clear_combo > 0) ? 1 : 0;
    vfx->y -= (game_state->combo > 0) ? 1 : 0;

    if (game_state->last_action_t_spin) {
        if (game_state->last_action_num_lines == 0) {
            strcpy(vfx->text, "t-spin");
            vfx->y--;
        } else if (game_state->last_action_num_lines == 1) {
            strcpy(vfx->text, "t-spin\nsingle");
            vfx->y -= 2;
        } else if (game_state->last_action_num_lines == 2) {
            strcpy(vfx->text, "t-spin\ndouble");
            vfx->y -= 2;
        } else if (game_state->last_action_num_lines == 3) {
            strcpy(vfx->text, "t-spin\ntriple");
            vfx->y -= 2;
        }
        vfx_enable(vfx, draw_vfx_action_t_spin);
    } else if (game_state->last_action_t_spin_mini) {
        if (game_state->last_action_num_lines == 0) {
            strcpy(vfx->text, "t-spin mini");
            vfx->y--;
            vfx_enable(vfx, draw_vfx_action_t_spin);
        } else if (game_state->last_action_num_lines == 1) {
            strcpy(vfx->text, "t-spin mini\nsingle");
            vfx->y -= 2;
            vfx_enable(vfx, draw_vfx_action_t_spin);
        } else if (game_state->last_action_num_lines == 2) {
            strcpy(vfx->text, "t-spin mini\ndouble");
            vfx->y -= 2;
            vfx_enable(vfx, draw_vfx_action_t_spin);
        }
    } else if (game_state->last_action_all_clear) {
        if (game_state->last_action_num_lines == 1) {
            strcpy(vfx->text, "single\nall clear");
            vfx->y -= 2;
            vfx_enable(vfx, draw_vfx_action_all_clear);
        } else if (game_state->last_action_num_lines == 2) {
            strcpy(vfx->text, "double\nall clear");
            vfx->y -= 2;
            vfx_enable(vfx, draw_vfx_action_all_clear);
        } else if (game_state->last_action_num_lines == 3) {
            strcpy(vfx->text, "triple\nall clear");
            vfx->y -= 2;
            vfx_enable(vfx, draw_vfx_action_all_clear);
        } else if (game_state->last_action_num_lines == 4) {
            if (game_state->tetris_all_clear_combo > 0) {
                strcpy(vfx->text, "b2b tetris\nall clear");
                vfx->y -= 2;
                vfx_enable(vfx, draw_vfx_action_all_clear);
            } else {
                strcpy(vfx->text, "tetris\nall clear");
                vfx->y -= 2;
                vfx_enable(vfx, draw_vfx_action_all_clear);
            }
        }
    } else if (game_state->last_action_num_lines == 1) {
        strcpy(vfx->text, "single");
        vfx->y--;
        vfx_enable(vfx, draw_vfx_action_single);
    } else if (game_state->last_action_num_lines == 2) {
        strcpy(vfx->text, "double");
        vfx->y--;
        vfx_enable(vfx, draw_vfx_action_double);
    } else if (game_state->last_action_num_lines == 3) {
        strcpy(vfx->text, "triple");
        vfx->y--;
        vfx_enable(vfx, draw_vfx_action_triple);
    } else if (game_state->last_action_num_lines == 4) {
        strcpy(vfx->text, "tetris");
        vfx->y--;
        vfx_enable(vfx, draw_vfx_action_tetris);
    }
}

void clear_vfx_action(VFX* vfx) {
    if (!vfx) {
        return;
    }
    for (size_t i = 0; i < strlen(vfx->text); ++i) {
        if (vfx->text[i] == '\n') {
            mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
            vfx->y++;
        }
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_action_single(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_double(VFX* vfx) {
    if (!vfx) {
        return;
    }
    
    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_triple(VFX* vfx) {
    if (!vfx) {
        return;
    }
    
    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }
    
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_tetris(VFX* vfx) {
    if (!vfx) {
        return;
    }
    
    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_t_spin(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }
    
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_all_clear(VFX* vfx) {
    if (!vfx) {
        return;
    }

    int16_t color_pair;
    if (vfx->frame_timer % 7 == 0) {
        color_pair = COLOR_PAIR_RED;
    } else if ((vfx->frame_timer + 1) % 7 == 0) {
        color_pair = COLOR_PAIR_ORANGE;
    } else if ((vfx->frame_timer + 2) % 7 == 0) {
        color_pair = COLOR_PAIR_YELLOW;
    } else if ((vfx->frame_timer + 3) % 7 == 0) {
        color_pair = COLOR_PAIR_GREEN;
    } else if ((vfx->frame_timer + 4) % 7 == 0) {
        color_pair = COLOR_PAIR_CYAN;
    } else if ((vfx->frame_timer + 5) % 7 == 0) {
        color_pair = COLOR_PAIR_BLUE;
    } else if ((vfx->frame_timer + 6) % 7 == 0) {
        color_pair = COLOR_PAIR_MAGENTA;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }
    
    wattron(vfx->game_window->content, COLOR_PAIR(color_pair));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(color_pair));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

bool vfx_check_combo(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0;
}

void vfx_enable_combo(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }
    
    vfx_disable(vfx);
    if (game_state->combo > 0) {
        sprintf(vfx->text, "%li x combo", game_state->combo);
        vfx->y = vfx->game_window->content_h;
        vfx->y -= (game_state->last_action_points > 0) ? 1 : 0; // use vfx_check_function
        vfx->y -= (game_state->difficult_clear_combo > 0) ? 1 : 0;
        vfx->y--;
        vfx_enable(vfx, draw_vfx_combo);
    }
}

void clear_vfx_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

bool vfx_check_b2b_combo(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0;
}

void vfx_enable_b2b_combo(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    vfx_disable(vfx);
    if (game_state->difficult_clear_combo > 0) {
        sprintf(vfx->text, "%li x b2b", game_state->difficult_clear_combo);
        vfx->y = vfx->game_window->content_h;
        vfx->y -= (game_state->last_action_points > 0) ? 1 : 0;
        vfx->y--;
        vfx_enable(vfx, draw_vfx_b2b_combo);
    }
}

void clear_vfx_b2b_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_b2b_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
    
    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

bool vfx_check_points(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0;
}

void vfx_enable_points(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    vfx_disable(vfx);
    if (game_state->last_action_points > 0) {
        sprintf(vfx->text, "%*lu", vfx->game_window->content_w, game_state->last_action_points);
        vfx->y = vfx->game_window->content_h;
        vfx->y--;
        vfx_enable(vfx, draw_vfx_points);
    }
}

void clear_vfx_points(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_points(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));

    if (vfx->frame_timer < LAST_ACTION_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

bool vfx_check_level_up(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->level_up_event_flag;
}

void vfx_enable_level_up(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    sprintf(vfx->text, "LEVEL%*lu", (int)(LEVEL_UP_VFX_W - strlen("LEVEL")), game_state->level);
    vfx->y = LEVEL_UP_VFX_Y;
    vfx->x = vfx->game_window->content_w/2 - strlen(vfx->text)/2;
    vfx_enable(vfx, draw_vfx_level_up);
}

void clear_vfx_level_up(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", (int)strlen(vfx->text), "");
}

void draw_vfx_level_up(VFX* vfx) {
    if (!vfx) {
        return;
    }

    int16_t color_pair;
    if (vfx->frame_timer % 7 == 0) {
        color_pair = COLOR_PAIR_RED;
    } else if ((vfx->frame_timer + 1) % 7 == 0) {
        color_pair = COLOR_PAIR_ORANGE;
    } else if ((vfx->frame_timer + 2) % 7 == 0) {
        color_pair = COLOR_PAIR_YELLOW;
    } else if ((vfx->frame_timer + 3) % 7 == 0) {
        color_pair = COLOR_PAIR_GREEN;
    } else if ((vfx->frame_timer + 4) % 7 == 0) {
        color_pair = COLOR_PAIR_CYAN;
    } else if ((vfx->frame_timer + 5) % 7 == 0) {
        color_pair = COLOR_PAIR_BLUE;
    } else if ((vfx->frame_timer + 6) % 7 == 0) {
        color_pair = COLOR_PAIR_MAGENTA;
    }

    if (vfx->frame_timer < LEVEL_UP_VFX_DIM_FRAMES) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(color_pair));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(color_pair));

    if (vfx->frame_timer < LEVEL_UP_VFX_DIM_FRAMES) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

bool vfx_check_stats_lines(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->last_action_num_lines > 0;
}

void vfx_enable_stats_lines(VFX* vfx, GameState* game_state) {
    if (!vfx) {
        return;
    }

    sprintf(vfx->text, "lines: %lu", game_state->lines);
    vfx->y = STATS_LINES_Y;
    vfx->x = STATS_LINES_X;
    vfx_enable(vfx, draw_vfx_stats_lines);
}

void clear_vfx_stats_lines(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
}

void draw_vfx_stats_lines(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, A_STANDOUT);
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, A_STANDOUT);
}

bool vfx_check_stats_level(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return false;
    }
    return game_state->level_up_event_flag;
}

void vfx_enable_stats_level(VFX* vfx, GameState* game_state) {
    if (!vfx) {
        return;
    }

    sprintf(vfx->text, "level: %lu", game_state->level);
    vfx->y = STATS_LEVEL_Y;
    vfx->x = STATS_LEVEL_X;
    vfx_enable(vfx, draw_vfx_stats_level);
}

void clear_vfx_stats_level(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
}

void draw_vfx_stats_level(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, A_STANDOUT);
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, A_STANDOUT);
}
