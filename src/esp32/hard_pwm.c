/**
 * Hardware PWM support on ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */

#include "gpio.h"

struct gpio_pwm gpio_pwm_setup(uint8_t pin, uint32_t cycle_time, uint8_t val)
{
    return (struct gpio_pwm){.pin = pin};
}

void gpio_pwm_write(struct gpio_pwm g, uint8_t val)
{
}