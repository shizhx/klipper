/**
 * Analog to digital support on ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */
#include "gpio.h"

struct gpio_adc gpio_adc_setup(uint8_t pin)
{
    return (struct gpio_adc){.pin = pin};
}

uint32_t gpio_adc_sample(struct gpio_adc g)
{
    return 0;
}

uint16_t gpio_adc_read(struct gpio_adc g)
{
    return 0;
}

void gpio_adc_cancel_sample(struct gpio_adc g)
{
}
