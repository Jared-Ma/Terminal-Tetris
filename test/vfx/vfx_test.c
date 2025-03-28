#include "vfx_test.h"
#include "vfx.h"
#include "draw.h"
#include "helper.h"

#include <stdint.h>
#include <time.h>


const uint16_t TARGET_FPS = 60;
const uint32_t TARGET_FRAME_TIME_NS = 1e9 / TARGET_FPS;

void run_vfx_test(VFXTest vfx_test, int8_t y_offset, int8_t x_offset) {
    VFX vfx;
    GameWindow game_window;
    struct timespec start_time, end_time;
    uint64_t frame_time_ns;

    vfx_test.test_function(&game_window, &vfx, y_offset, x_offset);

    while (vfx.enabled) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        draw_vfx_frame(&vfx);
        game_window_refresh(&game_window);

        mvprintw(y_offset, x_offset, "%*s", HOLD_WINDOW_W, "");
        mvprintw(y_offset, x_offset, "frame: %i", vfx.frame_timer);
        refresh();

        clock_gettime(CLOCK_MONOTONIC, &end_time);
        frame_time_ns = diff_timespec_ns(start_time, end_time);
        if (frame_time_ns < TARGET_FRAME_TIME_NS) {
            sleep_ns(TARGET_FRAME_TIME_NS - frame_time_ns);
        }
    }

    mvprintw(y_offset, x_offset, "%*s", HOLD_WINDOW_W, "");
    mvprintw(y_offset, x_offset, "frame: %i", vfx.frame_duration);
    refresh();
}
