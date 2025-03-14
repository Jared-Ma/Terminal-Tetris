#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "stats.h"
#include "logger.h"
#include "test_draw.h"


int main(void) {
    if (!debug_log_open("./logs/debug.txt")) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
