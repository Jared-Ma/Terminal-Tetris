#ifndef TEST_VFX_H
#define TEST_VFX_H
#include <stdbool.h>


bool test_vfx_get(void);

bool test_vfx_init(void);

bool test_vfx_enable(void);

bool test_vfx_disable(void);

bool test_vfx_enable_lock_piece(void);

bool test_vfx_enable_line_clear(void);

bool test_vfx_enable_hold_piece(void);

bool test_vfx_enable_next_piece(void);

bool test_vfx_enable_last_action_line_clear(void);

bool test_vfx_enable_last_action_t_spin(void);

bool test_vfx_enable_last_action_t_spin_mini(void);

bool test_vfx_enable_last_action_all_clear(void);

bool test_vfx_enable_last_action_combo(void);

bool test_vfx_enable_last_action_b2b(void);

bool test_vfx_enable_last_action_score(void);

bool test_vfx_enable_level_up(void);

bool test_vfx_enable_stats_lines(void);

bool test_vfx_enable_stats_level(void);

#endif
