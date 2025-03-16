#include "test_draw.h"
#include "draw.h"

#include "assert_trace.h"

#include <stdbool.h>


bool test_game_window_get(void) {
    GameWindow game_window = game_window_get(10, 20, 5, 5);
    ASSERT(game_window.border == NULL);
    ASSERT(game_window.content == NULL);
    ASSERT(game_window.border_h == 10);
    ASSERT(game_window.border_w == 20);
    ASSERT(game_window.border_y == 5);
    ASSERT(game_window.border_x == 5);
    ASSERT(game_window.content_h == game_window.border_h - 2);
    ASSERT(game_window.content_w == game_window.border_w - 2);
    ASSERT(game_window.content_y == game_window.border_y + 1);
    ASSERT(game_window.content_x == game_window.border_x + 1);
    return true;
}

bool test_game_window_init(void) {
    GameWindow* game_window = game_window_init(10, 20, 5, 5);
    ASSERT(game_window->border == NULL);
    ASSERT(game_window->content == NULL);
    ASSERT(game_window->border_h == 10);
    ASSERT(game_window->border_w == 20);
    ASSERT(game_window->border_y == 5);
    ASSERT(game_window->border_x == 5);
    ASSERT(game_window->content_h == game_window->border_h - 2);
    ASSERT(game_window->content_w == game_window->border_w - 2);
    ASSERT(game_window->content_y == game_window->border_y + 1);
    ASSERT(game_window->content_x == game_window->border_x + 1);
    game_window_destroy(game_window);
    return true;
}
