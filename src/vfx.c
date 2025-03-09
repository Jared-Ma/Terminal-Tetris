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

    if (game_state->last_action_hold_piece) {
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

void vfx_enable_last_action(
    VFX* vfx_last_action_type, 
    VFX* vfx_last_action_combo, 
    VFX* vfx_last_action_b2b, 
    VFX* vfx_last_action_score, 
    GameState* game_state
) {
    if (!vfx_last_action_type || !vfx_last_action_combo || !vfx_last_action_b2b || !vfx_last_action_score || !game_state) {
        return;
    }

    if (game_state->last_action_t_spin || game_state->last_action_t_spin_mini || game_state->last_action_num_lines > 0) {
        size_t start_y = vfx_last_action_type->game_window->content_h;

        if (game_state->last_action_points > 0) {
            sprintf(vfx_last_action_score->text, "%*lu", vfx_last_action_score->game_window->content_w, game_state->last_action_points);
            start_y--;
            vfx_last_action_score->y = start_y;
            vfx_enable(vfx_last_action_score, draw_vfx_last_action_score);
        }

        if (game_state->difficult_clear_combo > 0) {
            sprintf(vfx_last_action_b2b->text, "%li x b2b", game_state->difficult_clear_combo);
            start_y--;
            vfx_last_action_b2b->y = start_y;
            vfx_enable(vfx_last_action_b2b, draw_vfx_last_action_b2b);
        }

        if (game_state->combo > 0) {
            sprintf(vfx_last_action_combo->text, "%li x combo", game_state->combo);
            start_y--;
            vfx_last_action_combo->y = start_y;
            vfx_enable(vfx_last_action_combo, draw_vfx_last_action_combo);
        }

        if (game_state->last_action_t_spin) {
            if (game_state->last_action_num_lines == 0) {
                strcpy(vfx_last_action_type->text, "t-spin");
                start_y--;
                vfx_last_action_type->y = start_y;
            } else if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_last_action_type->text, "t-spin\nsingle");
                start_y -= 2;
                vfx_last_action_type->y = start_y;
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_last_action_type->text, "t-spin\ndouble");
                start_y -= 2;
                vfx_last_action_type->y = start_y;
            } else if (game_state->last_action_num_lines == 3) {
                strcpy(vfx_last_action_type->text, "t-spin\ntriple");
                start_y -= 2;
            }
            vfx_last_action_type->y = start_y;
            vfx_enable(vfx_last_action_type, draw_vfx_last_action_t_spin);
        } else if (game_state->last_action_t_spin_mini) {
            if (game_state->last_action_num_lines == 0) {
                strcpy(vfx_last_action_type->text, "t-spin mini");
                start_y--;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_t_spin);
            } else if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_last_action_type->text, "t-spin mini\nsingle");
                start_y -= 2;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_t_spin);
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_last_action_type->text, "t-spin mini\ndouble");
                start_y -= 2;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_t_spin);
            }
        } else if (game_state->last_action_perfect_clear) {
            if (game_state->last_action_num_lines == 1) {
                strcpy(vfx_last_action_type->text, "single\nperfect\nclear");
                start_y -= 3;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 2) {
                strcpy(vfx_last_action_type->text, "double\nperfect\nclear");
                start_y -= 3;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 3) {
                strcpy(vfx_last_action_type->text, "triple\nperfect\nclear");
                start_y -= 3;
                vfx_last_action_type->y = start_y;
                vfx_enable(vfx_last_action_type, draw_vfx_last_action_perfect_clear);
            } else if (game_state->last_action_num_lines == 4) {
                if (game_state->tetris_perfect_clear_combo > 0) {
                    strcpy(vfx_last_action_type->text, "b2b tetris\nperfect\nclear");
                    start_y -= 3;
                    vfx_last_action_type->y = start_y;
                    vfx_enable(vfx_last_action_type, draw_vfx_last_action_perfect_clear);
                } else {
                    strcpy(vfx_last_action_type->text, "tetris\nperfect\nclear");
                    start_y -= 3;
                    vfx_last_action_type->y = start_y;
                    vfx_enable(vfx_last_action_type, draw_vfx_last_action_perfect_clear);
                }
            }
        } else if (game_state->last_action_num_lines == 1) {
            strcpy(vfx_last_action_type->text, "single");
            start_y--;
            vfx_last_action_type->y = start_y;
            vfx_enable(vfx_last_action_type, draw_vfx_last_action_single);
        } else if (game_state->last_action_num_lines == 2) {
            strcpy(vfx_last_action_type->text, "double");
            start_y--;
            vfx_last_action_type->y = start_y;
            vfx_enable(vfx_last_action_type, draw_vfx_last_action_double);
        } else if (game_state->last_action_num_lines == 3) {
            strcpy(vfx_last_action_type->text, "triple");
            start_y--;
            vfx_last_action_type->y = start_y;
            vfx_enable(vfx_last_action_type, draw_vfx_last_action_triple);
        } else if (game_state->last_action_num_lines == 4) {
            strcpy(vfx_last_action_type->text, "tetris");
            start_y--;
            vfx_last_action_type->y = start_y;
            vfx_enable(vfx_last_action_type, draw_vfx_last_action_tetris);
        }
    }
}

void vfx_disable(VFX* vfx) {
    if (!vfx) {
        return;
    }

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
            vfx->reset_function(vfx);
            vfx_disable(vfx);
        }
    }
}

void draw_vfx_line_clear_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_DEFAULT);
}

void draw_vfx_line_clear_single(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
}

void draw_vfx_line_clear_double(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
}

void draw_vfx_line_clear_triple(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
}

void draw_vfx_line_clear_tetris(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
}

void draw_vfx_line_clear_t_spin(VFX* vfx) {
    if (!vfx) {
        return;
    }
    draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
}

void draw_vfx_line_clear_perfect(VFX* vfx) {
    if (!vfx) {
        return;
    }

    if (vfx->frame_timer % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_RED);
    } else if ((vfx->frame_timer + 1) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_ORANGE);
    } else if ((vfx->frame_timer + 2) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_YELLOW);
    } else if ((vfx->frame_timer + 3) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_GREEN);
    } else if ((vfx->frame_timer + 4) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_CYAN);
    } else if ((vfx->frame_timer + 5) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_BLUE);
    } else if ((vfx->frame_timer + 6) % 7 == 0) {
        draw_window_border(vfx->game_window, COLOR_PAIR_MAGENTA);
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

void draw_vfx_last_action_type_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_last_action_single(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_GREEN));
}

void draw_vfx_last_action_double(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_BLUE));
}

void draw_vfx_last_action_triple(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_YELLOW));
}

void draw_vfx_last_action_tetris(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_CYAN));
}

void draw_vfx_last_action_t_spin(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_MAGENTA));
}

void draw_vfx_last_action_perfect_clear(VFX* vfx) {
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
    
    wattron(vfx->game_window->content, COLOR_PAIR(color_pair));
    mvwprintw(vfx->game_window->content, vfx->y, vfx->x, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(color_pair));
}

void draw_vfx_last_action_combo_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_last_action_combo(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_RED));
}

void draw_vfx_last_action_b2b_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_last_action_b2b(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_ORANGE));
}

void draw_vfx_last_action_score_reset(VFX* vfx) {
    if (!vfx) {
        return;
    }
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%*s", vfx->game_window->content_w, "");
}

void draw_vfx_last_action_score(VFX* vfx) {
    if (!vfx) {
        return;
    }
    wattron(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));
    mvwprintw(vfx->game_window->content, vfx->y, 0, "%s", vfx->text);
    wattroff(vfx->game_window->content, COLOR_PAIR(COLOR_PAIR_DEFAULT));
}
