#include <ncurses.h>
#include <string.h>
#include "game_state.h"
#include "draw.h"
#include "vfx.h"
#include "logger.h"


VFX vfx_get(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration) {
    VFX visual_effect = {
        .game_window = game_window,
        .draw_function = NULL,
        .reset_function = reset_function,
        .frame_duration = frame_duration,
        .frame_timer = 0,
        .enabled = false,
        .y = 0,
        .x = 0,
        .text = { 0 }
    };
    return visual_effect;
}

VFX* vfx_init(GameWindow* game_window, draw_vfx_function* reset_function, uint16_t frame_duration) {
    VFX* vfx = malloc(sizeof(VFX));
    *vfx = vfx_get(game_window, reset_function, frame_duration);
    return vfx;
}

void vfx_destroy(VFX* vfx) {
    if (!vfx) {
        return;
    }
    *vfx = (VFX){ 0 };
    free(vfx);
}

void vfx_enable(VFX* vfx, draw_vfx_function* draw_function) {
    if (!vfx || !draw_function) {
        return;
    }
    vfx->draw_function = draw_function;
    vfx->frame_timer = vfx->frame_duration;
    vfx->enabled = true;
}

void vfx_enable_line_clear(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if ((game_state->last_action_t_spin || game_state->last_action_t_spin_mini) && game_state->last_action_num_lines > 0) {
        vfx_enable(vfx, draw_vfx_line_clear_t_spin);
    } else if (game_state->last_action_perfect_clear && game_state->last_action_num_lines > 0) {
        vfx_enable(vfx, draw_vfx_line_clear_perfect);
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

void vfx_enable_hold_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->hold_piece_event_flag) {
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
}

void vfx_enable_next_piece(VFX* vfx, GameState* game_state) {
    if (!vfx || !game_state) {
        return;
    }

    if (game_state->next_piece_event_flag) {
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
}

void vfx_enable_last_action(VFX* vfx_action, VFX* vfx_combo, VFX* vfx_b2b, VFX* vfx_score, GameState* game_state) {
    if (!vfx_action || !vfx_combo || !vfx_b2b || !vfx_score || !game_state) {
        return;
    }

    if (game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0) {
        size_t start_y = vfx_action->game_window->content_h;

        if (game_state->last_action_points > 0) {
            sprintf(vfx_score->text, "%*lu", vfx_score->game_window->content_w, game_state->last_action_points);
            start_y--;
            vfx_score->y = start_y;
            vfx_enable(vfx_score, draw_vfx_score);
        }

        if (game_state->difficult_clear_combo > 0) {
            sprintf(vfx_b2b->text, "%li x b2b", game_state->difficult_clear_combo);
            start_y--;
            vfx_b2b->y = start_y;
            vfx_enable(vfx_b2b, draw_vfx_b2b);
        }

        if (game_state->combo > 0) {
            sprintf(vfx_combo->text, "%li x combo", game_state->combo);
            start_y--;
            vfx_combo->y = start_y;
            vfx_enable(vfx_combo, draw_vfx_combo);
        }

        if (game_state->last_action_t_spin) {
            if (game_state->last_action_num_lines == 0) {
                strcpy(vfx_action->text, "t-spin");
                start_y--;
                vfx_action->y = start_y;
            } else if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_action->text, "t-spin\nsingle");
                start_y -= 2;
                vfx_action->y = start_y;
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_action->text, "t-spin\ndouble");
                start_y -= 2;
                vfx_action->y = start_y;
            } else if (game_state->last_action_num_lines == 3) {
                strcpy(vfx_action->text, "t-spin\ntriple");
                start_y -= 2;
            }
            vfx_action->y = start_y;
            vfx_enable(vfx_action, draw_vfx_action_t_spin);
        } else if (game_state->last_action_t_spin_mini) {
            if (game_state->last_action_num_lines == 0) {
                strcpy(vfx_action->text, "t-spin mini");
                start_y--;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_t_spin);
            } else if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_action->text, "t-spin mini\nsingle");
                start_y -= 2;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_t_spin);
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_action->text, "t-spin mini\ndouble");
                start_y -= 2;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_t_spin);
            }
        } else if (game_state->last_action_perfect_clear) {
            if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_action->text, "single\nperfect\nclear");
                start_y -= 3;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_action->text, "double\nperfect\nclear");
                start_y -= 3;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 3) {
                strcpy(vfx_action->text, "triple\nperfect\nclear");
                start_y -= 3;
                vfx_action->y = start_y;
                vfx_enable(vfx_action, draw_vfx_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 4) {
                if (game_state->tetris_perfect_clear_combo > 0) {
                    strcpy(vfx_action->text, "b2b tetris\nperfect\nclear");
                    start_y -= 3;
                    vfx_action->y = start_y;
                    vfx_enable(vfx_action, draw_vfx_action_perfect_clear);
                } else {
                    strcpy(vfx_action->text, "tetris\nperfect\nclear");
                    start_y -= 3;
                    vfx_action->y = start_y;
                    vfx_enable(vfx_action, draw_vfx_action_perfect_clear);
                }
            }
        } else if (game_state->last_action_num_lines == 1) {
            strcpy(vfx_action->text, "single");
            start_y--;
            vfx_action->y = start_y;
            vfx_enable(vfx_action, draw_vfx_action_single);
        } else if (game_state->last_action_num_lines == 2) {
            strcpy(vfx_action->text, "double");
            start_y--;
            vfx_action->y = start_y;
            vfx_enable(vfx_action, draw_vfx_action_double);
        } else if (game_state->last_action_num_lines == 3) {
            strcpy(vfx_action->text, "triple");
            start_y--;
            vfx_action->y = start_y;
            vfx_enable(vfx_action, draw_vfx_action_triple);
        } else if (game_state->last_action_num_lines == 4) {
            strcpy(vfx_action->text, "tetris");
            start_y--;
            vfx_action->y = start_y;
            vfx_enable(vfx_action, draw_vfx_action_tetris);
        }
    }
}

void vfx_enable_level_up(VFX* vfx, GameState* game_state) {
    if (game_state->level_up_event_flag) {
        sprintf(vfx->text, "LEVEL%*lu", 3, game_state->level);
        vfx->y = 5;
        vfx->x = vfx->game_window->content_w/2 - strlen(vfx->text)/2;
        vfx_enable(vfx, draw_vfx_level_up);
    }
}

void vfx_disable(VFX* vfx) {
    if (!vfx) {
        return;
    }
    vfx->reset_function(vfx);
    vfx->draw_function = NULL;
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
            vfx->draw_function(vfx);
            vfx->frame_timer--;
        } else {
            vfx_disable(vfx);
        }
    }
}

void draw_vfx_board_window_border(VFX* vfx, uint16_t color_pair) {
    wattron(vfx->game_window->border, COLOR_PAIR(color_pair));
    mvwaddch(vfx->game_window->border, 0, 0, ACS_ULCORNER);
    mvwaddch(vfx->game_window->border, 0, vfx->game_window->border_w - 1, ACS_URCORNER);
    mvwaddch(vfx->game_window->border, vfx->game_window->border_h - 1, 0, ACS_LLCORNER);
    mvwaddch(vfx->game_window->border, vfx->game_window->border_h - 1, vfx->game_window->border_w - 1, ACS_LRCORNER);
    mvwhline(vfx->game_window->border, 0, 1, ACS_HLINE, vfx->game_window->border_w - 2);
    mvwvline(vfx->game_window->border, 1, 0, ACS_VLINE, vfx->game_window->border_h - 2);
    mvwvline(vfx->game_window->border, 1, vfx->game_window->border_w - 1, ACS_VLINE, vfx->game_window->border_h - 2);
    mvwhline(vfx->game_window->border, vfx->game_window->border_h - 1, 1, ACS_HLINE, vfx->game_window->border_w/2 - 5);
    mvwhline(vfx->game_window->border, vfx->game_window->border_h - 1, vfx->game_window->border_w/2 + 4, ACS_HLINE, vfx->game_window->border_w/2 - 5);
    wattroff(vfx->game_window->border, COLOR_PAIR(color_pair));
}

void draw_vfx_line_clear_reset(VFX* vfx) {
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

void draw_vfx_line_clear_perfect(VFX* vfx) {
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

void draw_vfx_hold_piece_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_DEFAULT);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_DEFAULT);
}

void draw_vfx_hold_i_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_CYAN);
}

void draw_vfx_hold_j_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_BLUE);
}

void draw_vfx_hold_l_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_ORANGE);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_ORANGE);
}

void draw_vfx_hold_o_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_YELLOW);
}

void draw_vfx_hold_s_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_GREEN);
}

void draw_vfx_hold_t_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_MAGENTA);
}

void draw_vfx_hold_z_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_RED);
    draw_window_title(vfx->game_window, "HOLD", COLOR_PAIR_RED);
}

void draw_vfx_next_piece_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_DEFAULT);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_DEFAULT);
}

void draw_vfx_next_i_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_CYAN);
}

void draw_vfx_next_j_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_BLUE);
}

void draw_vfx_next_l_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_ORANGE);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_ORANGE);
}

void draw_vfx_next_o_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_YELLOW);
}

void draw_vfx_next_s_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_GREEN);
}

void draw_vfx_next_t_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_MAGENTA);
}

void draw_vfx_next_z_piece(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_RED);
    draw_window_title(vfx->game_window, "NEXT", COLOR_PAIR_RED);
}

void draw_vfx_action_reset(VFX* vfx) {
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

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_double(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_triple(VFX* vfx) {
    if (!vfx) {
        return;
    }
    
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    
    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }
    
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_tetris(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    
    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_t_spin(VFX* vfx) {
    if (!vfx) {
        return;
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_action_perfect_clear(VFX* vfx) {
    if (!vfx) {
        return;
    }

    uint16_t color_pair;
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

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }
    
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(color_pair));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(color_pair));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_combo_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_b2b_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_b2b(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
    
    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_score_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_score(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", vfx->game_window->content_w, "");
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}

void draw_vfx_level_up_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%*s", (int)strlen(vfx->text), "");
}

void draw_vfx_level_up(VFX* vfx) {
    if (!vfx) {
        return;
    }

    uint16_t color_pair;
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

    if (vfx->frame_timer < 30) {
        wattron(vfx->game_window->content, A_DIM);
    }

    wattron(vfx->game_window->content, COLOR_PAIR(color_pair));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(color_pair));

    if (vfx->frame_timer < 30) {
        wattroff(vfx->game_window->content, A_DIM);
    }
}
