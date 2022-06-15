/**
 * Use systimer of other ESP32 series processors
 * 
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 * 
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */

#include "hal/systimer_hal.h"
#include "board/misc.h"
#include "sched.h"

static systimer_hal_context_t s_timer;

/**
 * @brief convert microseconds to timer tick
 * 
 * @param us 
 * @return uint32_t 
 */
uint32_t timer_from_us(uint32_t us)
{
    return us;
}

/**
 * @brief read systimer tick
 * 
 * @return uint32_t 
 */
uint32_t timer_read_time(void)
{
    return (uint32_t)systimer_hal_get_time(&s_timer, 0)
}

/**
 * @brief init systimer
 * 
 */
void timer_init(void)
{
    systimer_hal_init(&s_timer)
}
DECL_INIT(timer_init);