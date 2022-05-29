/**
 * SPI support on ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */
#include "gpio.h"

struct spi_config spi_setup(uint32_t bus, uint8_t mode, uint32_t rate)
{
    return (struct spi_config){};
}

void spi_prepare(struct spi_config config)
{
}

void spi_transfer(struct spi_config config, uint8_t receive_data, uint8_t len,
                  uint8_t *data)
{
}