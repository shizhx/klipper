/**
 * Serial port support on ESP32 series processors
 *
 * Copyright (C) 2022 Shizhi Huang <main.shizhi@gmail.com>
 *
 * This file may be distributed under the terms of the GNU GPLv3 license.
 */
#include "board/serial_irq.h"

// callback provided by board specific code
void serial_enable_tx_irq(void)
{
}
