/**
 * uses TG0 LAC timer of the ESP32 to implement timer
 * 
 * implement from esp_timer_lac.c
 * 
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 * 
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */
#include "soc/soc.h"
#include "soc/timer_group_reg.h"
#include "esp_attr.h"

#include "board/misc.h"

/**
 * @brief Implementation of chip-specific part of esp_timer
 *
 * This implementation uses TG0 LAC timer of the ESP32. This timer is
 * a 64-bit up-counting timer, with a programmable compare value (called 'alarm'
 * hereafter). When the timer reaches compare value, interrupt is raised.
 * The timer can be configured to produce an edge or a level interrupt.
 */

/* Selects which Timer Group peripheral to use */
#define LACT_MODULE     0

#if LACT_MODULE == 0
#define INTR_SOURCE_LACT ETS_TG0_LACT_LEVEL_INTR_SOURCE
#define PERIPH_LACT PERIPH_TIMG0_MODULE
#elif LACT_MODULE == 1
#define INTR_SOURCE_LACT ETS_TG1_LACT_LEVEL_INTR_SOURCE
#define PERIPH_LACT PERIPH_TIMG1_MODULE
#else
#error "Incorrect the number of LACT module (only 0 or 1)"
#endif

/* Desired number of timer ticks per microsecond.
 * This value should be small enough so that all possible APB frequencies
 * could be divided by it without remainder.
 * On the other hand, the smaller this value is, the longer we need to wait
 * after setting UPDATE_REG before the timer value can be read.
 * If TICKS_PER_US == 1, then we need to wait up to 1 microsecond, which
 * makes esp_timer_impl_get_time function take too much time.
 * The value TICKS_PER_US == 2 allows for most of the APB frequencies, and
 * allows reading the counter quickly enough.
 */
#define TICKS_PER_US    2

/* Shorter register names, used in this file */
#define CONFIG_REG      (TIMG_LACTCONFIG_REG(LACT_MODULE))
#define COUNT_LO_REG    (TIMG_LACTLO_REG(LACT_MODULE))
#define UPDATE_REG      (TIMG_LACTUPDATE_REG(LACT_MODULE))

static inline uint32_t IRAM_ATTR esp_timer_impl_get_counter_reg(void)
{
    uint32_t lo;
    uint32_t lo_start = REG_READ(COUNT_LO_REG);
    uint32_t div = REG_GET_FIELD(CONFIG_REG, TIMG_LACT_DIVIDER);
    /* The peripheral doesn't have a bit to indicate that the update is done, so we poll the
     * lower 32 bit part of the counter until it changes, or a timeout expires.
     */
    REG_WRITE(UPDATE_REG, 1);
    do {
        lo = REG_READ(COUNT_LO_REG);
    } while (lo == lo_start && div-- > 0);

    return lo;
}

/**
 * @brief convert microseconds to timer tick
 * 
 * @param us microseconds
 * @return uint32_t timer tick
 */
uint32_t timer_from_us(uint32_t us)
{
    return us * TICKS_PER_US;
}

/**
 * @brief read timer tick
 * 
 * @return uint32_t 
 */
uint32_t timer_read_time(void)
{
    return esp_timer_impl_get_counter_reg();
}
